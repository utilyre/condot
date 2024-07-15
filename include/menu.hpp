#pragma once

#include <vector>
#include <raylib.h>

#include <asset_manager.hpp>
#include <state.hpp>
#include <entity.hpp>
#include <button.hpp>
#include <input.hpp>

class StartMenu : public Entity
{
public:
  StartMenu(State* state);

  void Update() override;
  void Render(const AssetManager& assets) const override;

private:
  State* m_State;
  Button m_ButtonStart;
  Button m_ButtonExit;
};

class PlayerPickMenu : public Entity
{
public:
  PlayerPickMenu(State* state);

  void Update() override;
  void Render(const AssetManager& assets) const override;

private:
  struct Row {
    Input Name;
    Input Age;
  };

private:
  State* m_State;
  float m_Padding;
  Rectangle m_Dimensions;
  std::vector<Row> m_Rows;
};
