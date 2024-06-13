#pragma once

#include <string>
#include <vector>

#include <card.hpp>

class Player {
public:
  Player();
  Player(std::string name, std::string color, int age);
  ~Player();

  const std::string& GetName() const;
  int GetAge() const;
  void AddCard(Card* card);
  Card* TakeCard(const std::string& name);
  void PrintCards();

private:
  std::vector<Card*> m_Cards;
  std::string m_Name;
  std::string m_Color;
  int m_Age;
};
