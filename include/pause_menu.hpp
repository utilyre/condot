#pragma once 

#include <asset_manager.hpp>
#include <entity.hpp>
#include <button.hpp>
#include <state.hpp>
#include <event.hpp>
#include <help_menu.hpp>

class PauseMenu : public Entity
{
  public:
    PauseMenu(State*, Event*);
    void Update() override;
    void Render(const AssetManager&) const override;

  private:
    Button m_PauseMenuButton;
    Button m_ContinueButton;
    Button m_HelpButton;
    Button m_ExitButton;
    Button m_BackButton;
    State* m_State;
    Event* m_QuitEvent;
    bool m_ShowHelpMenu;
    HelpMenu m_HelpMenu;
};
