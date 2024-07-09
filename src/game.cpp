#include <algorithm>
#include <climits>
#include <raylib.h>

#include <game.hpp>
#include <player.hpp>
#include <card.hpp>
#include <mercenary.hpp>

void Game::Start()
{
  SetTargetFPS(60);

  // TODO: add/customize players through menu
  m_Players.emplace_back("John", RED, 10 , Position::TOP);
  m_Players.emplace_back("Jane", GREEN, 2 , Position::RIGHT);
  m_Players.emplace_back("Alex", BLUE, 1 , Position::BOTTOM);
  m_Players.emplace_back("Theo", GRAY, 4 ,Position::LEFT);

  InitiateBattle();

  // NOTE: do NOT modify
  while (!WindowShouldClose())
  {
    Update();

    BeginDrawing();
    Render();
    EndDrawing();
  }
}

void Game::Update()
{
  // PlayCard();

  for (Player& p : m_Players)
  {
    p.Update();
  }

  m_Map.Update();
}

void Game::Render() const
{
  ClearBackground(RAYWHITE);

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
