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
#include <status_bar.hpp>
#include <help_menu.hpp>
#include <pause_menu.hpp>
#include <file_stream.hpp>
#include <vector>

// #define DEBUG

static const float AUTOSAVE_INTERVAL = 30.0f;

Game::Game()
: m_Stopped(false),
  m_FavorMarkerChooserIndex(-1),
  m_AutoSaveTimer(AUTOSAVE_INTERVAL, true),
  m_MainMenu(&m_State, &m_LoadEvent, &m_StopEvent, &m_InitiateBattleEvent),
  m_CustomizationMenu(&m_State, &m_InitiateBattleEvent, &m_AddPlayerEvent),
  m_PauseMenu(&m_State, &m_StopEvent, &m_SaveEvent),
  m_Map(&m_State, &m_Players, &m_Turn, &m_FavorMarkerChooserIndex),
  m_StatusBar(&m_State, &m_Season)
{
  m_StopEvent.Subscribe([this](auto, auto) { Stop(); });
  m_InitiateBattleEvent.Subscribe([this](auto, auto) { InitiateBattle(); });
  m_RotateTurnEvent.Subscribe([this](auto,auto data) { RotateTurn(std::any_cast<bool*>(data)); });
  m_RestartBattleEvent.Subscribe([this](auto , auto) { RestartBattle(); });
  m_AddPlayerEvent.Subscribe([this](auto, std::any data) {
    PlayerInfo p = std::any_cast<PlayerInfo>(data);
    m_Players.emplace_back(p.name, p.age, p.color, p.position);
    m_Players.back().Init(
      &m_State,
      &m_Season,
      &m_RotateTurnEvent,
      &m_RestartBattleEvent,
      &m_TakeFavorMarkerEvent
    );

    std::clog << "INFO: Player \"" << p.name << "\" added.\n";
  });
  m_SaveEvent.Subscribe([this](auto, auto) { Save(); });
  m_LoadEvent.Subscribe([this](auto, auto) { Load(); });
  m_TakeFavorMarkerEvent.Subscribe([this](Entity* sender, auto) {
    Player* chooser = dynamic_cast<Player*>(sender);
    for (size_t i = 0; i < m_Players.size(); i++)
    {
      if (&m_Players[i] == chooser)
      {
        m_FavorMarkerChooserIndex = i;
        break;
      }
    }
  });

  m_StatusBar.Set(&m_Players);
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

void Game::Serialize(StreamWriter& w, const Game& game)
{
  w.WriteRaw(game.m_State);
  w.WriteRaw(game.m_Turn);
  w.WriteRaw(game.m_FavorMarkerChooserIndex);
  w.WriteRaw(game.m_Season);
  w.WriteObject(game.m_Map);
  w.WriteVector(game.m_Players);
  w.WriteVector(game.m_Deck);
}

void Game::Deserialize(StreamReader& r, Game& game)
{
  r.ReadRaw(game.m_State);
  r.ReadRaw(game.m_Turn);
  r.ReadRaw(game.m_FavorMarkerChooserIndex);
  r.ReadRaw(game.m_Season);
  r.ReadObject(game.m_Map);

  r.ReadVector(game.m_Players);
  for (Player& player : game.m_Players)
  {
    player.Init(
      &game.m_State,
      &game.m_Season,
      &game.m_RotateTurnEvent,
      &game.m_RestartBattleEvent,
      &game.m_TakeFavorMarkerEvent
    );
  }

  r.ReadVector(game.m_Deck);
}

void Game::Update()
{
  float dt = GetFrameTime();

  if (m_State.Get() == State::PLAYING_CARD)
  {
    m_AutoSaveTimer.Tick(dt);
    if (m_AutoSaveTimer.Finished())
    {
      Save();
    }
  }

  m_MainMenu.Update();
  m_CustomizationMenu.Update();
  m_StatusBar.Update();
  m_PauseMenu.Update();
  
  m_Map.Update();
  if (m_Players.size() > m_Turn) m_Players[m_Turn].Update();
  for (size_t i = 0; i < m_Players.size(); i++)
  {
    if (i != m_Turn) m_Players[i].Update();
  }
}

void Game::Render() const
{
  DrawTexture(m_Assets.Background, 0, 0, WHITE);

  m_MainMenu.Render(m_Assets);
  m_CustomizationMenu.Render(m_Assets);
  m_PauseMenu.Render(m_Assets);
  
  m_Map.Render(m_Assets);
  if (m_Players.size() > m_Turn) m_Players[m_Turn].Render(m_Assets);
  for (size_t i = 0; i < m_Players.size(); i++)
  {
    if (i != m_Turn) m_Players[i].Render(m_Assets);
  }

  m_StatusBar.Render(m_Assets);
#ifdef DEBUG
  DrawText(TextFormat("(%d,%d)", GetMouseX(), GetMouseY()), 10, 10, 30, WHITE);
#endif
}

void Game::ResetCards()
{
  m_Deck.clear();
  m_Season = Season::NONE;

  for(Player& p : m_Players)
  {
    p.Reset();
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
  for (Player& player : m_Players)
  {
    for (int i = 0; i < 10; i++)
    {
      player.AddCard(m_Deck.back());
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
  FixPosition();
  ResetCards();
  DealCards();
}

void Game::RotateTurn(bool* Status){
  
  size_t StartPos = (m_Turn);
  for(size_t i{},passed{1}; i < m_Players.size(); ++i)
  {
    size_t EndPos = (StartPos + passed) % m_Players.size();
    while(m_Players[EndPos].IsPassed()){
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
    
    m_Players[StartPos].SetPosition(m_Players[EndPos].GetPosition());
    
    if(i == m_Players.size() - 1){
      m_Turn = StartPos;
      m_Players[m_Turn].SetPosition(Position::BOTTOM_LEFT);
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

  for (auto p : m_Players)
  {
    BishopNum += p.GetBishop();
  }

  for (int counter = 0; counter < BishopNum; ++counter)
  {
    for (const auto& p : m_Players)
    {
      if (BiggestNum < p.GetBiggestNum()){
        BiggestNum = p.GetBiggestNum();
      }
    }

    for (auto& p : m_Players)
    {
      p.DeleteCard(BiggestNum);
    }
    BiggestNum = 0;
  }
  
  for (const auto& p : m_Players)
  {
    if (BiggestNum < p.GetBiggestNum()){
      BiggestNum = p.GetBiggestNum();
    }
  }
   
  for (size_t i = 0; i < m_Players.size(); i++)
  {
    int strength = m_Players[i].CalculateScore(BiggestNum);
    
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

  if (potentialWinners.size() == 1) 
  {
    m_Map.GetBattleMarker()->SetRuler(m_Players[potentialWinners[0]]);
    m_Turn = potentialWinners[0];
  }
  else
  {
    m_Map.ResetBattleMarker();
  }

  std::mt19937 mt(m_RandDev());
  std::uniform_int_distribution<size_t> dist(0, potentialWinners.size() - 1);
  m_Turn = potentialWinners[dist(mt)];

  if (auto bm = m_Map.GetBattleMarker())
  {
    std::clog
      << "INFO: "
      << bm->GetRuler()->name
      << "conquered "
      << bm->GetName()
      << '\n';
  }
  potentialWinners.clear();

  for (size_t index = 0; index < m_Players.size(); ++index)
  {
    int Num = m_Players[index].GetSpy();
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
    m_Turn = potentialWinners[0];
  }
  
  m_State.Set(State::PLACING_BATTLE_MARKER);
}

void Game::FixPosition()
{
  for(size_t i = 0; i < m_Players.size(); ++i)
  {
    m_Players[(m_Turn + i) % m_Players.size()].SetPosition(static_cast<Position>(i));
  }
}

void Game::RestartBattle()
{
  FindRegionConquerer();

  m_State.Set(
    m_FavorMarkerChooserIndex < 0
    ? State::PLACING_BATTLE_MARKER
    : State::PLACING_FAVOR_MARKER
  );

  auto winner = m_Map.FindWinners();
  if(!winner.empty())
  {
    std::clog << "INFO: Winner is " << winner[0].name << '\n';
    exit(1);
  }
  ResetCards();
  FixPosition();
  DealCards();
}

void Game::Save()
{
  FileStream stream("save.dat", std::ios::out | std::ios::binary);
  stream.WriteObject(*this);
  std::clog << "INFO: Saved game to 'save.dat' file\n";
}

void Game::Load()
{
  FileStream stream("save.dat", std::ios::in | std::ios::binary);
  stream.ReadObject(*this);
  std::clog << "INFO: Loaded game from 'save.dat' file\n";
}
