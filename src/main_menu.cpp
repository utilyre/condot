#include <filesystem>
#include <raylib.h>

#include <state.hpp>
#include <event.hpp>
#include <asset_manager.hpp>
#include <main_menu.hpp>

static const int BUTTON_WIDTH = 800;
static const int BUTTON_HEIGHT = 100;
static const float SPACING = 20.0f;

MainMenu::MainMenu(
  State* state,
  Event* loadEvent,
  Event* quitEvent,
  Event* initiateBattleEvent
)
: m_State(state),
  m_LoadEvent(loadEvent),
  m_QuitEvent(quitEvent),
  m_InitiateBattleEvent(initiateBattleEvent),
  m_ButtonContinue("Continue", Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    (GetScreenHeight() - BUTTON_HEIGHT) / 2.0f - BUTTON_HEIGHT - SPACING,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  }),
  m_ButtonStart("Start", Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    (GetScreenHeight() - BUTTON_HEIGHT) / 2.0f,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  }),
  m_ButtonExit("Exit", Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    (GetScreenHeight() - BUTTON_HEIGHT) / 2.0f + BUTTON_HEIGHT + SPACING,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  })
{
  if (!std::filesystem::exists("save.dat"))
  {
    m_ButtonContinue.Disable();
  }
}

void MainMenu::Update()
{
  if (m_State->Get() != State::MAIN_MENU)
  {
    return;
  }

  m_ButtonContinue.Update();
  m_ButtonStart.Update();
  m_ButtonExit.Update();

  if (m_ButtonContinue.Pressed())
  {
    m_LoadEvent->Notify(this);
  }
  if (m_ButtonStart.Pressed())
  {
    m_State->Set(State::CUSTOMIZATION_MENU);
  }
  if (m_ButtonExit.Pressed())
  {
    m_QuitEvent->Notify(this);
  }
}

void MainMenu::Render(const AssetManager& assets) const
{
  if (m_State->Get() != State::MAIN_MENU)
  {
    return;
  }

  m_ButtonContinue.Render(assets);
  m_ButtonStart.Render(assets);
  m_ButtonExit.Render(assets);
}
