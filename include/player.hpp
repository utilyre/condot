#pragma once

#include <string>
#include <raylib.h>
#include <vector>
 
#include <asset_manager.hpp>
#include <entity.hpp>
#include <card.hpp>
#include <mercenary.hpp>

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
  Player(const std::string& name, Color color, int age, Position position);

  void Update() override;
  void Render(const AssetManager& assets) const override;

  int GetAge() const;
  void AddCard(Card card);

private:
  void RenderCards(const AssetManager& assets, Vector2 cordinate, float rotation) const;
  
private:
  std::string m_Name;
  Color m_Color;
  int m_Age;
  Position m_Position;
  std::vector<Card> m_Cards;
  std::vector<Mercenary> m_Row;
};
