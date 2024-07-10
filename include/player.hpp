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
  bool IsPassed();
  void SetPosition(const Position& position);
  const Position& GetPosition() const;
private:
  void RenderCards(const AssetManager& assets, Vector2 cordinate, float rotation) const;
  void RenderRows(const AssetManager& assets, Vector2 cordinate, float rotation) const;
  bool IsCollided(AssetManager& assets, const Position& position);
  const Card& TakeCard(const size_t& position);
  void Pass();
  void AddRowCard(const Card& card);
private:
  std::string m_Name;
  Color m_Color;
  int m_Age;
  Position m_Position;
  std::vector<Card> m_Cards;
  std::vector<Card> m_Row;
  bool m_IsPassed;
};
