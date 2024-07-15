#pragma once

#include <asset_manager.hpp>
#include <state.hpp>
#include <entity.hpp>
#include <button.hpp>

class MainMenu : public Entity
{
public:
  MainMenu(State* state);

  void Update() override;
  void Render(const AssetManager& assets) const override;

private:
  State* m_State;

  Button m_ButtonStart;
  Button m_ButtonExit;
};
