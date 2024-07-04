#pragma once

#include <string>
#include <raylib.h>

#include <asset_manager.hpp>
#include <drawable.hpp>

enum class Position
{
  TOP,
  RIGHT,
  BOTTOM,
  LEFT,
};

class Player : public Drawable
{
public:
  Player(const std::string& name, Color color, Position position);
  ~Player() override;

  void Draw(const AssetManager& assets) const override;

private:
  std::string m_Name;
  Color m_Color;
  Position m_Position;
};
