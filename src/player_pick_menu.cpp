#include <string>
#include <raylib.h>

#include <state.hpp>
#include <menu.hpp>

static const int MENU_WIDTH = 1600;
static const int MENU_HEIGHT = 900;

PlayerPickMenu::PlayerPickMenu(State* state)
: m_State(state)
{
}

void PlayerPickMenu::Update()
{
  if (m_State->Get() != State::PLAYER_PICK_MENU)
  {
    return;
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

  Rectangle menuDimensions = {
    (width - MENU_WIDTH) / 2.0f,
    (height - MENU_HEIGHT) / 2.0f,
    MENU_WIDTH,
    MENU_HEIGHT
  };

  DrawRectangleRounded(menuDimensions, 0.1f, 0, WHITE);
}
