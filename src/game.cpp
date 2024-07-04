#include <raylib.h>

#include <game.hpp>

Game::Game()
{
  int monitor = GetCurrentMonitor();
  int width = GetMonitorWidth(monitor);
  int height = GetMonitorHeight(monitor);
  InitWindow(width, height, "Condottiere");

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
  int monitor = GetCurrentMonitor();
  int width = GetMonitorWidth(monitor);
  int height = GetMonitorHeight(monitor);

  ClearBackground(RAYWHITE);

  DrawTexture(m_Assets.Map, (width - m_Assets.Map.width) / 2, (height - m_Assets.Map.height) / 2, WHITE);
}
