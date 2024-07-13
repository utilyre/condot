#include <string>
#include <raylib.h>

#include <state.hpp>
#include <menu.hpp>

static const int MENU_WIDTH = 1600;
static const int MENU_HEIGHT = 900;

PlayerPickMenu::PlayerPickMenu(State* state)
: m_State(state),
  m_PlayerCount(3)
{
}

void PlayerPickMenu::Update()
{
  if (m_State->Get() != State::PLAYER_PICK_MENU)
  {
    return;
  }

  if (IsKeyPressed(KEY_UP))
  {
    m_PlayerCount++;
  }
  if (IsKeyPressed(KEY_DOWN))
  {
    m_PlayerCount--;
  }
}

void PlayerPickMenu::Render(const AssetManager& assets) const
{
  if (m_State->Get() != State::PLAYER_PICK_MENU)
  {
    return;
  }

  int width = GetScreenWidth();
  int height = GetScreenHeight();

  int padding = 50;
  Rectangle menuDimensions = {
    (width - MENU_WIDTH) / 2.0f,
    (height - MENU_HEIGHT) / 2.0f,
    MENU_WIDTH,
    MENU_HEIGHT
  };

  DrawRectangleRounded(menuDimensions, 0.1f, 0, WHITE);

  DrawText(
    TextFormat("Players: %d (use <up> and <down> keys to adjust)", m_PlayerCount),
    menuDimensions.x + padding,
    menuDimensions.y + padding,
    25,
    BLACK
  );
}
