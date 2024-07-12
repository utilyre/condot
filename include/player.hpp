#pragma once

#include <string>
#include <raylib.h>
#include <vector>
 
#include <asset_manager.hpp>
#include <state.hpp>
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
  Player(State* state, const std::string& name, Color color, int age, Position position);

  void Update() override;
  void Render(const AssetManager& assets) const override;

  int GetAge() const;
  void AddCard(Card card);
  bool IsPassed();
  void SetPosition(const Position& position);
  const Position& GetPosition() const;
private:
  bool PlayCard();
  void RenderCards(const AssetManager& assets, Vector2 cordinate, float rotation) const;
  void RenderRows(const AssetManager& assets, Vector2 cordinate, float rotation) const;
  void PickCard(const size_t& index);
  void Pass();
private:
  State* m_State;
  std::string m_Name;
  Color m_Color;
  int m_Age;
  Position m_Position;
  std::vector<Card> m_Cards;
  std::vector<Mercenary> m_Row;
  bool m_IsPassed;
};
