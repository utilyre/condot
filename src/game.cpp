#include <any>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <climits>
#include <any>
#include <raylib.h>

#include <game.hpp>
#include <state.hpp>
#include <event.hpp>
#include <player.hpp>
#include <entity.hpp>
#include <card.hpp>
#include <mercenary.hpp>
#include <main_menu.hpp>
#include <customization_menu.hpp>

#define DEBUG

Game::Game()
: m_Stopped(false),
  m_MainMenu(&m_State, &m_StopEvent),
  m_CustomizationMenu(&m_State, &m_InitiateBattleEvent, &m_AddPlayerEvent),
  m_Map(&m_State)
{
  m_StopEvent.Subscribe([this](auto, auto) { Stop(); });
  m_InitiateBattleEvent.Subscribe([this](auto, auto) { InitiateBattle(); });
  m_RotateTurnEvent.Subscribe([this](auto,auto data) { RotateTurn(std::any_cast<bool*>(data)); });
  m_RestartBattleEvent.Subscribe([this](auto , auto) { RestartBattle(); });
  m_AddPlayerEvent.Subscribe([this](auto, std::any data) {
    Player* player = std::any_cast<Player*>(data);
    player->SetContext(&m_State, &m_RotateTurnEvent, &m_RestartBattleEvent);
    m_Players.push_back(player);

    std::clog << "INFO: Player \"" << player->GetName() << "\" added.\n";
  });
}

Game::~Game()
{
  for (Player* p : m_Players)
  {
    delete p;
  }
}

void Game::Start()
{
  ToggleFullscreen();
  SetExitKey(KEY_NULL);
  SetTargetFPS(60);

  // NOTE: do NOT modify
  while (!m_Stopped && !WindowShouldClose())
  {
    Update();
    BeginDrawing();
      Render();
    EndDrawing();
  }
}

void Game::Stop()
{
  m_Stopped = true;
}

void Game::Update()
{
  m_MainMenu.Update();
  m_CustomizationMenu.Update();

  m_Map.Update();
  if (m_Players.size() > m_Turn) m_Players[m_Turn]->Update();
  for (Player* p : m_Players)
  {
    if (m_Players[m_Turn] != p) p->Update();
  }
}

void Game::Render() const
{
  DrawTexture(m_Assets.Background, 0, 0, WHITE);

  m_MainMenu.Render(m_Assets);
  m_CustomizationMenu.Render(m_Assets);

  m_Map.Render(m_Assets);
  if (m_Players.size() > m_Turn) m_Players[m_Turn]->Render(m_Assets);
  for (const Player* p : m_Players)
  {
    if (m_Players[m_Turn] != p) p->Render(m_Assets);
  }
  
#ifdef DEBUG
  DrawText(TextFormat("(%d,%d)", GetMouseX(), GetMouseY()), 10, 10, 30, WHITE);
#endif
}

void Game::ResetCards()
{
  m_Deck.clear();
  m_State.Set(State::NONE);

  for(Player* p : m_Players)
  {
    p->Reset();
  }
  
  m_Deck.insert(m_Deck.end(), 10, Card::MERCENARY_1);
  m_Deck.insert(m_Deck.end(), 8, Card::MERCENARY_2);
  m_Deck.insert(m_Deck.end(), 8, Card::MERCENARY_3);
  m_Deck.insert(m_Deck.end(), 8, Card::MERCENARY_4);
  m_Deck.insert(m_Deck.end(), 8, Card::MERCENARY_5);
  m_Deck.insert(m_Deck.end(), 8, Card::MERCENARY_6);
  m_Deck.insert(m_Deck.end(), 8, Card::MERCENARY_10);

  m_Deck.insert(m_Deck.end(), 6, Card::BISHOP);
  m_Deck.insert(m_Deck.end(), 16, Card::SCARECROW);
  m_Deck.insert(m_Deck.end(), 3, Card::TURNCOAT);
  m_Deck.insert(m_Deck.end(), 3, Card::WINTER);
  m_Deck.insert(m_Deck.end(), 3, Card::SPRING);
  m_Deck.insert(m_Deck.end(), 6, Card::DRUMMER);
  m_Deck.insert(m_Deck.end(), 12, Card::SPY);
  m_Deck.insert(m_Deck.end(), 3, Card::HEROINE);

  std::default_random_engine rng(m_RandDev());
  std::shuffle(m_Deck.begin(), m_Deck.end(), rng);
}

void Game::DealCards()
{
  for (Player* player : m_Players)
  {
    for (int i = 0; i < 10; i++)
    {
      player->AddCard(m_Deck.back());
      m_Deck.pop_back();
    }
  }
}

size_t Game::FindBattleInstigatorIndex() const
{
  int min = INT_MAX;
  std::vector<size_t> candidateIndices;
  for (size_t i = 0; i < m_Players.size(); i++)
  {
    int age = m_Players[i]->GetAge();
    if (age < min)
    {
      min = age;
      candidateIndices.clear();
      candidateIndices.push_back(i);
    }
    else if (age == min)
    {
      candidateIndices.push_back(i);
    }
  }

  std::mt19937 mt(m_RandDev());
  std::uniform_int_distribution<size_t> dist(0, candidateIndices.size() - 1);
  return candidateIndices[dist(mt)];
}

void Game::InitiateBattle()
{
  m_Turn = FindBattleInstigatorIndex();
  FixPosition();
  ResetCards();
  DealCards();
}

void Game::RotateTurn(bool* Status){
  
  size_t StartPos = (m_Turn);
  for(size_t i{},passed{1}; i < m_Players.size(); ++i)
  {
    size_t EndPos = (StartPos + passed) % m_Players.size();
    while(m_Players[EndPos]->IsPassed()){
      passed++;
      EndPos = ( StartPos + passed ) % m_Players.size();
      i++;
    }

    if (passed == m_Players.size() && !(*Status))
    {
      RestartBattle();
      *Status = false;
      return;
    }
    else
    {
      *Status = true;
    }
    
    m_Players[StartPos]->SetPosition(m_Players[EndPos]->GetPosition());
    
    if(i == m_Players.size() - 1){
      m_Turn = StartPos;
      m_Players[m_Turn]->SetPosition(Position::BOTTOM_LEFT);
    }
    StartPos = EndPos;
    passed = 1;
  } 
}

void Game::FindRegionConquerer()
{
  int SpyNum = 0;
  int BishopNum = 0;
  int BiggestNum = 0;
  int max_strength = 0;
  std::vector<size_t> potentialWinners;

  for (size_t index = 0; index < m_Players.size(); ++index)
  {
    int Num = m_Players[index]->GetSpy();
    if (SpyNum < Num)
    {
      SpyNum = Num;
      potentialWinners.clear();
      potentialWinners.push_back(index);
    }
    
    else if (Num == SpyNum)
    {
     potentialWinners.push_back(index); 
    }
  }
  
  if (potentialWinners.size() == 1) 
  {
    m_Map.GetBattleMarker()->SetRuler(m_Players[potentialWinners[0]]);
    m_State.Set(State::PLACING_BATTLE_MARKER);
    return;
  }

  for (auto p : m_Players)
  {
    BishopNum += p->GetBishop();
  }

  for (int counter = 0; counter < BishopNum; ++counter)
  {
    for (const auto& p : m_Players)
    {
      if (BiggestNum < p->GetBiggestNum()){
        BiggestNum = p->GetBiggestNum();
      }
    }

    for (auto& p : m_Players)
    {
      p->DeleteCard(BiggestNum);
    }
    BiggestNum = 0;
  }
  
  for (const auto& p : m_Players)
  {
    if (BiggestNum < p->GetBiggestNum()){
      BiggestNum = p->GetBiggestNum();
    }
  }
   
  for (size_t i = 0; i < m_Players.size(); i++)
  {
    int strength = m_Players[i]->CalculateScore(BiggestNum);
    
    if (strength > max_strength)
    {
      max_strength = strength;
      potentialWinners.clear();
      potentialWinners.push_back(i);
    }
    else if (strength == max_strength) 
    {
      potentialWinners.push_back(i);
    }
  }

  if (potentialWinners.size() == 1) {
    m_Map.GetBattleMarker()->SetRuler(m_Players[potentialWinners[0]]);
  }
  else
  {
    m_Map.ResetBattleMarker();
  }

  std::mt19937 mt(m_RandDev());
  std::uniform_int_distribution<size_t> dist(0, potentialWinners.size() - 1);
  m_Turn = potentialWinners[dist(mt)];
  
  m_State.Set(State::PLACING_BATTLE_MARKER);
}

void Game::FixPosition()
{
  for(size_t i = 0; i < m_Players.size(); ++i)
  {
    m_Players[(m_Turn + i) % m_Players.size()]->SetPosition(static_cast<Position>(i));
  }
}

void Game::RestartBattle()
{
  FindRegionConquerer();
  ResetCards();
  FixPosition();
  DealCards();
}
