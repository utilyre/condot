#include <raylib.h>

#include <asset_manager.hpp>
#include <button.hpp>
#include <pause_menu.hpp>
#include <state.hpp>
#include <event.hpp>
#include <unordered_map>

static const float BUTTON_WIDTH = 800;
static const float BUTTON_HEIGHT = 100;

PauseMenu::PauseMenu(State* state, Event* quit, Event* save) : 
  m_PauseMenuButton("Pause",Rectangle{GetScreenWidth() - 120.0f, 10, 120, 70}),
  m_ContinueButton("Continue", Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    (GetScreenHeight() - BUTTON_HEIGHT) / 2.0f - 240,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  }),
  m_HelpButton("Help", Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    (GetScreenHeight() - BUTTON_HEIGHT) / 2.0f,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  }),
  m_ExitButton("Exit", Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    (GetScreenHeight() - BUTTON_HEIGHT) / 2.0f + 120,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  }),
  m_BackButton("Back", Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    GetScreenHeight() - 120.0f,
    BUTTON_WIDTH,
    BUTTON_HEIGHT,
    }),
  m_SaveButton("Save", Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    (GetScreenHeight() - BUTTON_HEIGHT) / 2.0f - 120.0f,
    BUTTON_WIDTH,
    BUTTON_HEIGHT,
    }),
  m_State(state),
  m_QuitEvent(quit),
  m_SaveEvent(save),
  m_ShowHelpMenu(false)
  {}
  
void PauseMenu::Render(const AssetManager& assets) const
{
  if (m_State->Get() == State::MAIN_MENU ||
      m_State->Get() == State::CUSTOMIZATION_MENU ||
      m_State->Get() == State::PLACING_BATTLE_MARKER ||
      m_State->Get() == State::PLACING_FAVOR_MARKER) 
  {
    return;
  }
  if (!m_ShowHelpMenu) 
  {
    if (m_State->Get() != State::PAUSE_MENU) 
    {
      m_PauseMenuButton.Render(assets);
    }

    if (m_State->Get() == State::PAUSE_MENU) 
    {
      m_ContinueButton.Render(assets);
      m_HelpButton.Render(assets);
      m_ExitButton.Render(assets);
      m_SaveButton.Render(assets);
    }
  }
  else 
  {
    m_HelpMenu.Render(assets);
    if (!m_HelpMenu.IsGettingDetail()) 
    {
      m_BackButton.Render(assets);
    }
  }
}

void PauseMenu::Update()
{
  if (m_State->Get() == State::MAIN_MENU ||
      m_State->Get() == State::CUSTOMIZATION_MENU ||
      m_State->Get() == State::PLACING_BATTLE_MARKER ||
      m_State->Get() == State::PLACING_FAVOR_MARKER) 
  {
    return;
  }

  if (!m_ShowHelpMenu) 
  {
    m_PauseMenuButton.Update();
    m_ContinueButton.Update();
    m_ExitButton.Update();
    m_SaveButton.Update();
  }
  else 
  {
    m_HelpMenu.Update();  
  }

  m_HelpButton.Update();
  

  if (m_PauseMenuButton.Pressed()) 
  {
    m_State->Set(State::PAUSE_MENU);
  }
  
  else if (m_ContinueButton.Pressed() &&
           m_State->Get() == State::PAUSE_MENU) 
  {
    m_State->Set(m_State->GetPrev());
  }

  else if (m_HelpButton.Pressed() &&
           m_State->Get() == State::PAUSE_MENU)
  {
    m_ShowHelpMenu = true;
  }

  else if (m_BackButton.Pressed() &&
           m_State->Get() == State::PAUSE_MENU)
  {
    m_ShowHelpMenu = false;
  }

  else if (m_ExitButton.Pressed() &&
           m_State->Get() == State::PAUSE_MENU)
  {
   m_QuitEvent->Notify(this);   
  }

  else if (m_SaveButton.Pressed()) 
  {
    m_SaveEvent->Notify(this);
  }

  if (!m_HelpMenu.IsGettingDetail()) 
  {
    m_BackButton.Update();
  }
}
