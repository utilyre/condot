#pragma once

#include <vector>
#include <string>
#include <raylib.h>

#include <asset_manager.hpp>
#include <state.hpp>
#include <event.hpp>
#include <entity.hpp>
#include <button.hpp>
#include <input.hpp>

class CustomizationMenu : public Entity
{
public:
  CustomizationMenu(
    State* state,
    Event* initiateBattleEvent,
    Event* addPlayerEvent
  );

  void Update() override;
  void Render(const AssetManager& assets) const override;

private:
  void Continue();

private:
  struct PlayerRow {
    Input Name;
    Input Age;
  };

private:
  State* m_State;
  Event* m_InitiateBattleEvent;
  Event* m_AddPlayerEvent;

  Rectangle m_Dimensions;

  Button m_MenuButton;
  Button m_ContinueButton;
  Button m_IncreasePlayersButton;
  Button m_DecreasePlayersButton;
  std::vector<PlayerRow> m_PlayerRows;
  std::string m_ErrorMsg;
};
