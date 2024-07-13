#include "asset_manager.hpp"
#include <raylib.h>

#include <state.hpp>
#include <menu.hpp>

static const int BUTTON_WIDTH = 800;
static const int BUTTON_HEIGHT = 100;

StartMenu::StartMenu(State* state)
: m_State(state),
  m_ButtonStart("Start", 50, Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    (GetScreenHeight() - BUTTON_HEIGHT) / 2.0f - 60,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  }),
  m_ButtonExit("Exit", 50, Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    (GetScreenHeight() - BUTTON_HEIGHT) / 2.0f + 60,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  })
{
}

void StartMenu::Update()
{
  if (m_State->Get() == State::MENU)
  {
    m_ButtonStart.Update();
    m_ButtonExit.Update();

    if (m_ButtonStart.Hovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      m_State->Set(State::INITIATING_BATTLE);
    }
    if (m_ButtonExit.Hovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
      // TODO: signal game to exit
    }
  }
}

void StartMenu::Render(const AssetManager& assets) const
{
  if (m_State->Get() == State::MENU)
  {
    m_ButtonStart.Render(assets);
    m_ButtonExit.Render(assets);
  }
}
