#pragma once

#include <vector>
#include <raylib.h>

#include <asset_manager.hpp>
#include <state.hpp>
#include <entity.hpp>
#include <button.hpp>
#include <input.hpp>

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
