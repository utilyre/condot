#pragma once

#include <string>
#include <raylib.h>
#include <vector>

#include <asset_manager.hpp>
#include <state.hpp>
#include <event.hpp>
#include <entity.hpp>
#include <card.hpp>
#include <mercenary.hpp>
#include <button.hpp>
#include <season.hpp>

enum class Position {
  BOTTOM_LEFT,
  LEFT,
  TOP_LEFT,
  TOP_RIGHT,
  RIGHT,
  BOTTOM_RIGHT,
};

class Player : public Entity
{
public:
  Player(const std::string& name, int age, Color color, Position position);

  void SetContext(
    State* state,
    Season* season,
    Event* rotateTurnEvent,
    Event* restartBattleEvent
  );

  void Update() override;
  void Render(const AssetManager& assets) const override;

  const std::string& GetName() const;
  int GetAge() const;
  void AddCard(Card card);
  bool IsPassed();
  void SetPosition(const Position& position);
  Position GetPosition() const;
  int CalculateScore(int C = 0) const;
  int GetBiggestNum() const;
  void Reset();
  void DeleteCard(int BNum);
  int GetBishop() const;
  int GetSpy() const;
  int GetHeroine() const;
  int GetDrummer() const;
  Color GetColor() const;
private:
  bool PlayCard();
  void RenderCards(const AssetManager& assets, Vector2 cordinate, float rotation, float ratio) const;
  void RenderRows(const AssetManager& assets, Vector2 cordinate, float rotation, float ratio) const;
  void Pass();
  void Add(size_t index);
  bool RetrieveCard();
  bool PickCard(const size_t& index);

private:
  State* m_State;
  Season* m_Season;

  Event* m_RotateTurnEvent;
  Event* m_RestartBattleEvent;

  std::string m_Name;
  Color m_Color;
  int m_Age;
  Position m_Position;
  std::vector<Card> m_Cards;
  std::vector<Mercenary> m_Row;
  bool m_IsPassed;
  unsigned int m_Spy;
  unsigned int m_Heroine;
  unsigned int m_Drummer;
  unsigned int m_Bishop;
  Button m_PassButton;
};
