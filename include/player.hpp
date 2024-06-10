#pragma once

#include <future>
#include <memory>
#include <string>

#include <vector>
#include <memory.h>
#include <cards.hpp>

class Player {
public:
  Player();
  Player(std::string name, std::string color, int age);
  const std::string& GetName() const;
  int GetAge() const;
  std::vector<std::shared_ptr<Cards>>& GetAvailableCards();
  std::vector<std::shared_ptr<Cards>>& GetPlayedCards();
  void PrintCards();
  void PlayCard(std::string cardname);
private:
  
  std::vector<std::shared_ptr<Cards>> AvailableCards;
  std::vector<std::shared_ptr<Cards>> PlayedCards;  
  std::string                         m_Name;
  std::string                         m_Color;
  int                                 m_Age;
};
