#include <raylib.h>

#include <game.hpp>

int main()
{
  int m = GetCurrentMonitor();
  InitWindow(GetMonitorWidth(m), GetMonitorHeight(m), "Condottiere");
  ToggleFullscreen();

  {
    Game game;
    game.Start();
  }

  CloseWindow();
}
