#include <iostream>
#include <algorithm>
#include <climits>
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

Game::Game()
: m_Stopped(false),
  m_MainMenu(&m_State, &m_StopEvent),
  m_CustomizationMenu(&m_State, &m_InitiateBattleEvent),
  m_Map(&m_State)
{
  m_StopEvent.Register([this](auto, auto) { Stop(); });
  m_InitiateBattleEvent.Register([this](auto, auto) { InitiateBattle(); });
  m_RotateTurnEvent.Register([this](auto, auto) { RotateTurn(); });
}

void Game::Start()
{
  ToggleFullscreen();
  SetExitKey(KEY_NULL);
  SetTargetFPS(60);

  // TODO: add/customize players through menu
  m_Players.emplace_back(&m_State, &m_RotateTurnEvent, "abbas", ORANGE, 6 , Position::TOP_RIGHT);
  m_Players.emplace_back(&m_State, &m_RotateTurnEvent, "amir", PURPLE, 3 , Position::RIGHT);
  m_Players.emplace_back(&m_State, &m_RotateTurnEvent, "John", RED, 10 , Position::BOTTOM_RIGHT);
  m_Players.emplace_back(&m_State, &m_RotateTurnEvent, "Alex", BLUE, 1 , Position::BOTTOM_LEFT);
  m_Players.emplace_back(&m_State, &m_RotateTurnEvent, "Theo", GRAY, 4 ,Position::LEFT);
  m_Players.emplace_back(&m_State, &m_RotateTurnEvent, "Jane", GREEN, 2 , Position::TOP_LEFT);

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
  
  m_Players[m_Turn].Update();
  for (Player& p : m_Players)
  {
    if(&m_Players[m_Turn] != &p) p.Update();
  }
  m_Map.Update();
  //FindRegionConquerer();
}

void Game::Render() const
{
  DrawTexture(m_Assets.Background, 0, 0, WHITE);

  m_MainMenu.Render(m_Assets);
  m_CustomizationMenu.Render(m_Assets);

  for (const Player& p : m_Players)
  {
    p.Render(m_Assets);
  }

  m_Map.Render(m_Assets);

 // DrawText(TextFormat("(%d, %d)", GetMouseX(), GetMouseY()), 10, 10, 30, BLACK);
  DrawText(TextFormat("(%d)",GetCurrentPlayer().CalculateScore()), 10, 10, 30, BLACK);
  
}

void Game::ResetCards()
{
  m_Deck.clear();

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
  for (Player& player : m_Players)
  {
    for (int i = 0; i < 10; i++)
    {
      player.AddCard(m_Deck.back());
      m_Deck.pop_back();
    }
  }
}

const Player& Game::GetCurrentPlayer() const
{
  return m_Players[m_Turn];
}

size_t Game::FindBattleInstigatorIndex() const
{
  int min = INT_MAX;
  std::vector<size_t> candidateIndices;
  for (size_t i = 0; i < m_Players.size(); i++)
  {
    int age = m_Players[i].GetAge();
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
  ResetCards();
  DealCards();
}

void Game::RotateTurn(){
  size_t StartPos = (m_Turn);
  for(size_t i{},passed{1}; i < m_Players.size(); ++i){
    
    size_t EndPos = (StartPos + passed) % m_Players.size();
    while(m_Players[EndPos].IsPassed()){
      passed++;
      EndPos = ( StartPos + passed ) % m_Players.size();
      i++;
    }
    
    m_Players[StartPos].SetPosition(m_Players[EndPos].GetPosition());
    
    if(i == m_Players.size() - 1){
      m_Turn = StartPos;
      m_Players[m_Turn].SetPosition(Position::BOTTOM_LEFT);
    }
    StartPos = EndPos;
    passed = 1;
  }
  std::cout << std::endl;
}

void Game::FindRegionConquerer()
{
  int BNum{};
  int WinnerScore{};
  
  for(const auto& p : m_Players)
  {
    if (BNum < p.GetBiggestNum()){
      BNum = p.GetBiggestNum();
    }
  }

  for(auto& p : m_Players)
  {
    if(WinnerScore < p.CalculateScore(BNum))
    {
      WinnerScore = p.CalculateScore(BNum);
      m_Map.GetBattleMarker()->SetRuler(p);
    }
  }
  
}
