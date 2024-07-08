#include <cstdio>
#include <memory>
#include <raylib.h>
#include <algorithm>
#include <iostream>

#include <game.hpp>
#include <player.hpp>
#include <mercenary.hpp>
#include <bishop.hpp>
#include <drummer.hpp>
#include <heroine.hpp>
#include <spy.hpp>
#include <string>
#include <turncoat.hpp>
#include <scarecrow.hpp>
#include <type_traits>

void Game::Menu(){
  Start();
}
void Game::Start()
{
  SetTargetFPS(60);

  // TODO: add/customize players through menu
  m_Players.emplace_back("John", RED, 10 , Position::TOP);
  m_Players.emplace_back("Jane", GREEN, 2 , Position::RIGHT);
  m_Players.emplace_back("Alex", BLUE, 1 , Position::BOTTOM);
  m_Players.emplace_back("Theo", GRAY, 4 ,Position::LEFT);
  m_Turn = FindWarInstigator();
  InsertCards();
  ShuffleCards();
  DealCards();
  while (!WindowShouldClose())
  {
    Update();
    BeginDrawing();
    Render();
    PlayCard();
    EndDrawing();
  }
}

void Game::Update()
{
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
}

void Game::InsertCards(){
  for(size_t i{1}; i < 11; i++){
    for(size_t j{}; j < 10; j++){
      if( i == 7 || i == 8 || i == 9){
        break;
      }
      else if( i != 1 && j > 7){
        break;
      }
      std::unique_ptr<Card> card = std::make_unique<Mercenary>(i);
      m_Cards.push_back(std::move(card));
    }
  }
  for(size_t i{} ; i < 6; ++i){
    std::unique_ptr<Card> card = std::make_unique<Bishop>();
    m_Cards.push_back(std::move(card));
    card = nullptr;
    card = std::make_unique<Drummer>();
    m_Cards.push_back(std::move(card));
  }
  for(size_t i{}; i < 3; ++i){
    std::unique_ptr<Card> card = std::make_unique<Heroine>();
    m_Cards.push_back(std::move(card));
    card = nullptr;
    card = std::make_unique<Turncoat>();
    m_Cards.push_back(std::move(card));
  }
  for(size_t i{}; i < 12; ++i){
    std::unique_ptr<Card> card = std::make_unique<Spy>();
    m_Cards.push_back(std::move(card));
    
  }
  for(size_t i{}; i < 16; ++i){
    std::unique_ptr<Card> card = std::make_unique<Scarecrow>();
    m_Cards.push_back(std::move(card));
  }
  
  
  
}

void Game::ShuffleCards(){
  std::default_random_engine rng(m_RandDev());
  std::shuffle(m_Cards.begin(), m_Cards.end(), rng);
}


void Game::DealCards(){
  for(auto& player : m_Players){
    for(size_t i{}; i < 10; i++){
      player.AddCard(std::move(m_Cards.back()));
      m_Cards.pop_back();
    }
  }
}

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

void Game::PlayCard(){
  auto& p = m_Players[m_Turn];
  if(p.IsCollided(m_Assets,p.GetPosition()) && 
     IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
    NextTurn();
  }
  else if (CheckCollisionPointRec(GetMousePosition(),(Rectangle){420, 950, 70, 50}) &&
           IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
    NextTurn();
    m_Players[(m_Turn + 1) % m_Players.size()].Pass();
  }
  DrawText(TextFormat("pos x: %i\npos y: %i",(int)GetMouseX(),(int)GetMouseY()),100 ,100 ,20 ,BLACK);
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
    std::cout << StartPos << " " << EndPos << " " << i << std::endl;
    StartPos = EndPos;
    passed = 1;
  } 
  return true;
}
