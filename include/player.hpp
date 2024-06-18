#pragma once

#include <string>
#include <vector>
#include <memory>

#include <card.hpp>
#include <normalcard.hpp>

class Player {
public:
  Player(std::string name, std::string color, int age);

  const std::string& GetName() const;
  int GetAge() const;
  void AddCard(std::unique_ptr<Card>&& card);
  std::unique_ptr<Card> TakeCard(const std::string& name);
  void AddDrawnNormalCard(std::unique_ptr<NormalCard>&& card);
  const std::vector<std::unique_ptr<Card>>& GetCards() const;
  const std::vector<std::unique_ptr<NormalCard>>& GetDrawnNormalCards() const;
  void Pass();
  bool IsPassed() const;
  int GetStrength() const;
  void ResetPassed();
  void ResetDrawnCards();
private:
  std::string m_Name;
  std::string m_Color;
  int m_Age;
  bool m_Passed;
  std::vector<std::unique_ptr<Card>> m_Cards;
  std::vector<std::unique_ptr<NormalCard>> m_DrawnNormalCards;
};
