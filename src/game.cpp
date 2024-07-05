#include <raylib.h>

#include <game.hpp>
#include <player.hpp>
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
