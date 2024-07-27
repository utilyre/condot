#pragma once

#include <string>
#include <raylib.h>
#include <unordered_map>
#include <vector>

#include <asset_manager.hpp>
#include <state.hpp>
#include <event.hpp>
#include <entity.hpp>
#include <card.hpp>
#include <mercenary.hpp>
#include <button.hpp>

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
  Player(
    State* state,
    Event* rotateTurnEvent,
    const std::string& name,
    Color color,
    int age,
    Position position
  );

  void Update() override;
  void Render(const AssetManager& assets) const override;

  int GetAge() const;
  void AddCard(Card card);
  bool IsPassed();
  void SetPosition(const Position& position);
  const Position& GetPosition() const;
  std::vector<Card>& GetCards();
  void PickCard(const size_t& index);
  const Color GetColor() const;
private:
  bool PlayCard();
  void RenderCards(const AssetManager& assets, Vector2 cordinate, float rotation) const;
  void RenderRows(const AssetManager& assets, Vector2 cordinate, float rotation) const;
  void Pass();
  void Add(const size_t& index);
private:
  State* m_State;
  Event* m_RotateTurnEvent;
  std::string m_Name;
  Color m_Color;
  int m_Age;
  Position m_Position;
  std::vector<Card> m_Cards;
  std::vector<Mercenary> m_Row;
  bool m_IsPassed;
  Button m_PassButton;
  std::unordered_map<std::string , int> m_s;
};
