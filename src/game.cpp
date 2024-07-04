#include <raylib.h>

#include <game.hpp>

void Game::Start()
{
  SetTargetFPS(60);

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

  int length = 3 * height / 4;
  int thickness = 200;
  DrawRectangle((width - length) / 2, 0, length, thickness, RED); // top
  DrawRectangle(width - thickness, (height - length) / 2, thickness, length, GREEN); // right
  DrawRectangle((width - length) / 2, height - thickness, length, thickness, BLUE); // bottom
  DrawRectangle(0, (height - length) / 2, thickness, length, GRAY); // left

  DrawTexture(m_Assets.Map, (width - m_Assets.Map.width) / 2, (height - m_Assets.Map.height) / 2, WHITE);
}
