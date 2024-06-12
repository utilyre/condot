#pragma once

#include <string>
#include <vector>

#include <memory.h>
#include <cards.hpp>

class Player {
public:
  Player();
  Player(std::string name, std::string color, int age);
  ~Player();

  const std::string& GetName() const;
  int GetAge() const;
  std::vector<Card*>& GetAvailableCards();
  std::vector<Card*>& GetPlayedCards();
  void PrintCards();

private:
  std::vector<Card*> m_AvailableCards;
  std::vector<Card*> m_PlayedCards;  
  std::string m_Name;
  std::string m_Color;
  int m_Age;
};
