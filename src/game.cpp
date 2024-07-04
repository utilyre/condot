#include <raylib.h>

#include <game.hpp>
#include <player.hpp>

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
}

void Game::Render() const
{
  int monitor = GetCurrentMonitor();
  int width = GetMonitorWidth(monitor);
  int height = GetMonitorHeight(monitor);

  ClearBackground(RAYWHITE);

  for (const Player& p : m_Players)
  {
    p.Draw(m_Assets);
  }

  DrawTexture(m_Assets.Map, (width - m_Assets.Map.width) / 2, (height - m_Assets.Map.height) / 2, WHITE);
}
