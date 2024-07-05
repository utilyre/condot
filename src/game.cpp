#include <raylib.h>
#include <algorithm>

#include <game.hpp>
#include <player.hpp>
#include <mercenary.hpp>
#include <bishop.hpp>
#include <drummer.hpp>
#include <heroine.hpp>
#include <spy.hpp>

void Game::Menu(){
  BeginDrawing();
  while (!WindowShouldClose()) {
    ClearBackground(RAYWHITE);
    DrawText("1. New Game",GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 ,40 , DARKGRAY);
    DrawText("2. Load Game",GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 100 , 40,DARKGRAY );
    if(IsKeyPressed(KEY_ONE)){
      Start();
    }
    EndDrawing();
  }
}
void Game::Start()
{
  SetTargetFPS(60);

  // TODO: add/customize players through menu
  m_Players.emplace_back("John", RED, Position::TOP);
  m_Players.emplace_back("Jane", GREEN, Position::RIGHT);
  m_Players.emplace_back("Alex", BLUE, Position::BOTTOM);
  m_Players.emplace_back("Theo", GRAY, Position::LEFT);
  InsertCards();
  ShuffleCards();
  DealCards();
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
  }
  for(size_t i{}; i < 12; ++i){
    std::unique_ptr<Card> card = std::make_unique<Spy>();
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
