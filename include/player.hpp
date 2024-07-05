#pragma once

#include <string>
#include <raylib.h>
#include <vector>
#include <memory>
 
#include <asset_manager.hpp>
#include <entity.hpp>
#include <card.hpp>

enum class Position
{
  TOP,
  RIGHT,
  BOTTOM,
  LEFT,
};

class Player : public Entity
{
public:
  Player(const std::string& name, Color color, Position position);

  void Update() override;
  void Render(const AssetManager& assets) const override;
  void RenderCards(const AssetManager& assets , Vector2 cordinate , float rotation) const ; 
private:
  std::string m_Name;
  Color m_Color;
  Position m_Position;
  std::vector<std::unique_ptr<Card>> m_Cards;
};
