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
  ~Player();
  const std::string&   GetName() const;
  int                  GetAge() const;
  std::vector<Cards*>& GetAvailableCards();
  std::vector<Cards*>& GetPlayedCards();
  void                 PrintCards();
  private:
  
  std::vector<Cards*> AvailableCards;
  std::vector<Cards*> PlayedCards;  
  std::string         m_Name;
  std::string         m_Color;
  int                 m_Age;
};
