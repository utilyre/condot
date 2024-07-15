#include <algorithm>
#include <climits>
#include <raylib.h>

#include <game.hpp>
#include <player.hpp>
#include <card.hpp>
#include <mercenary.hpp>
#include <menu.hpp>

Game::Game()
: m_Stopped(false),
  m_MainMenu(&m_State),
  m_PlayerPickMenu(&m_State),
  m_Map(&m_State)
{
}

void Game::Start()
{
  SetTargetFPS(60);

  // TODO: add/customize players through menu
  m_Players.emplace_back(&m_State, "John", RED, 10 , Position::TOP);
  m_Players.emplace_back(&m_State, "Jane", GREEN, 2 , Position::RIGHT);
  m_Players.emplace_back(&m_State, "Alex", BLUE, 1 , Position::BOTTOM);
  m_Players.emplace_back(&m_State, "Theo", GRAY, 4 ,Position::LEFT);

  // NOTE: do NOT modify
  while (!WindowShouldClose())
  {
    if (m_Stopped)
    {
      break;
    }

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
  if (m_State.Get() == State::INITIATING_BATTLE)
  {
    InitiateBattle();
    m_State.Set(State::PLACING_BATTLE_MARKER);
  }

  m_MainMenu.Update();
  m_PlayerPickMenu.Update();

  for (Player& p : m_Players)
  {
    p.Update();
  }

  m_Map.Update();
}

void Game::Render() const
{
  DrawTexture(m_Assets.Background, 0, 0, WHITE);

  m_MainMenu.Render(m_Assets);
  m_PlayerPickMenu.Render(m_Assets);

  for (const Player& p : m_Players)
  {
    p.Render(m_Assets);
  }

  m_Map.Render(m_Assets);

  DrawText(TextFormat("(%d, %d)", GetMouseX(), GetMouseY()), 10, 10, 30, BLACK);
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

bool Game::NextTurn(){
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
      m_Players[m_Turn].SetPosition(Position::BOTTOM);
    }
  
    StartPos = EndPos;
    passed = 1;
  } 
  return true;
}
