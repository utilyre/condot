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
  Player(const std::string& name, Color color, size_t age, Position position);

  void Update() override;
  void Render(const AssetManager& assets) const override;
  void RenderCards(const AssetManager& assets, Vector2 cordinate, float rotation) const;
  void AddCard(std::unique_ptr<Card>&& card);
  void AddDrawnCard(std::unique_ptr<Card>&& card);
  void SetPosition(const Position& position);
  void Pass();
  bool IsCollided(AssetManager& assets,const  Position& position);
  std::unique_ptr<Card> TakeCard(size_t& pos);
  const size_t&                             GetAge() const;
  const std::string                         GetName() const;
  const std::vector<std::unique_ptr<Card>>& GetCards() const; 
  const std::vector<std::unique_ptr<Card>>& GetDrawnCards() const;
  const Position&                           GetPosition() const;
  bool                                      IsPassed() const;
  
private:
  std::string m_Name;
  Color m_Color;
  Position m_Position;
  size_t m_Age;
  std::vector<std::unique_ptr<Card>> m_Cards;
  std::vector<std::unique_ptr<Card>> m_DrawnCards; 
  bool m_Passed;
};
