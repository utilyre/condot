#include <raylib.h>

#include <game.hpp>

Game::Game()
{
  InitWindow(1600, 900, "Condottiere");
  m_Assets.Load();
  SetTargetFPS(60);
  ToggleFullscreen();
}

Game::~Game()
{
  CloseWindow();
}

void Game::Start()
{
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
}

void Game::Render() const
{
  ClearBackground(RAYWHITE);
  DrawTexture(m_Assets.Map, 0, 0, WHITE);
}
