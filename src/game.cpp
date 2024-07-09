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
  m_Turn = FindWarInstigator();

  ResetCards();
  // DealCards();

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
  m_Cards.clear();

  m_Cards.insert(m_Cards.end(), 10, Card::MERCENARY_1);
  m_Cards.insert(m_Cards.end(), 8, Card::MERCENARY_2);
  m_Cards.insert(m_Cards.end(), 8, Card::MERCENARY_3);
  m_Cards.insert(m_Cards.end(), 8, Card::MERCENARY_4);
  m_Cards.insert(m_Cards.end(), 8, Card::MERCENARY_5);
  m_Cards.insert(m_Cards.end(), 8, Card::MERCENARY_6);
  m_Cards.insert(m_Cards.end(), 8, Card::MERCENARY_10);

  m_Cards.insert(m_Cards.end(), 6, Card::BISHOP);
  m_Cards.insert(m_Cards.end(), 16, Card::SCARECROW);
  m_Cards.insert(m_Cards.end(), 3, Card::TURNCOAT);
  m_Cards.insert(m_Cards.end(), 3, Card::WINTER);
  m_Cards.insert(m_Cards.end(), 3, Card::SPRING);
  m_Cards.insert(m_Cards.end(), 6, Card::DRUMMER);
  m_Cards.insert(m_Cards.end(), 12, Card::SPY);
  m_Cards.insert(m_Cards.end(), 3, Card::HEROINE);

  std::default_random_engine rng(m_RandDev());
  std::shuffle(m_Cards.begin(), m_Cards.end(), rng);
}

// void Game::DealCards(){
//   for(auto& player : m_Players){
//     for(size_t i{}; i < 10; i++){
//       player.AddCard(std::move(m_Cards.back()));
//       m_Cards.pop_back();
//     }
//   }
// }

const Player& Game::GetCurrentPlayer() const{
  return m_Players[m_Turn];
}

size_t Game::FindWarInstigator() {
  int min = INT_MAX;
  std::vector<size_t> potentialInstigators;
  for(size_t i = 0; i < m_Players.size() ; i++){
    int age = m_Players[i].GetAge();
    if (age < min) {
      min = age;
      potentialInstigators.clear();
      potentialInstigators.push_back(i);
    } else if (age == min) {
      potentialInstigators.push_back(i);
    }
  }

  std::mt19937 mt(m_RandDev());
  std::uniform_int_distribution<size_t> dist(0, potentialInstigators.size() - 1);
  return potentialInstigators[dist(mt)];
}

// void Game::PlayCard(){
//   auto& p = m_Players[m_Turn];
//   if(p.IsCollided(m_Assets,p.GetPosition()) && 
//      IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
//     NextTurn();
//   }
//   else if (CheckCollisionPointRec(GetMousePosition(),(Rectangle){420, 950, 70, 50}) &&
//            IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
//     NextTurn();
//     m_Players[(m_Turn + 1) % m_Players.size()].Pass();
//   }
// }

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
