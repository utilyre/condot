#pragma once

#include <asset_manager.hpp>
#include <state.hpp>
#include <event.hpp>
#include <entity.hpp>
#include <button.hpp>

class MainMenu : public Entity
{
public:
  MainMenu(
    State* state,
    Event* loadEvent,
    Event* quitEvent,
    Event* initiateBattleEvent
  );

  void Update() override;
  void Render(const AssetManager& assets) const override;

private:
  State* m_State;
  Event* m_LoadEvent;
  Event* m_QuitEvent;
  Event* m_InitiateBattleEvent;

  Button m_ButtonContinue;
  Button m_ButtonStart;
  Button m_ButtonExit;
};
