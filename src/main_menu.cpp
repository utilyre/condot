#include <raylib.h>

#include <state.hpp>
#include <event.hpp>
#include <asset_manager.hpp>
#include <main_menu.hpp>

static const int BUTTON_WIDTH = 800;
static const int BUTTON_HEIGHT = 100;

MainMenu::MainMenu(State* state, Event* quitEvent)
: m_State(state),
  m_QuitEvent(quitEvent),
  m_ButtonStart("Start", Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    (GetScreenHeight() - BUTTON_HEIGHT) / 2.0f - 60,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  }),
  m_ButtonExit("Exit", Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    (GetScreenHeight() - BUTTON_HEIGHT) / 2.0f + 60,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  })
{
}

void MainMenu::Update()
{
  if (m_State->Get() != State::MAIN_MENU)
  {
    return;
  }

  m_ButtonStart.Update();
  m_ButtonExit.Update();

  if (m_ButtonStart.Pressed())
  {
    m_State->Set(State::CUSTOMIZATION_MENU);
  }
  if (m_ButtonExit.Pressed())
  {
    m_QuitEvent->Raise(this, nullptr);
  }
}

void MainMenu::Render(const AssetManager& assets) const
{
  if (m_State->Get() != State::MAIN_MENU)
  {
    return;
  }

    m_ButtonStart.Render(assets);
    m_ButtonExit.Render(assets);
}
