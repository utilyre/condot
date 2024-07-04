#include <iostream>
#include <raylib.h>

#include <game.hpp>

Game::Game()
{
  InitWindow(GetWidth(), GetHeight(), "Condottiere");
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
  DrawTexture(m_Assets.Map, (GetWidth() - m_Assets.Map.width) / 2, (GetHeight() - m_Assets.Map.height) / 2, WHITE);
}

int Game::GetWidth() const
{
  int monitor = GetCurrentMonitor();
  return GetMonitorWidth(monitor);
}

int Game::GetHeight() const
{
  int monitor = GetCurrentMonitor();
  return GetMonitorHeight(monitor);
}
