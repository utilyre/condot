#pragma once

#include <string>

class Player {
public:
  Player();
  Player(std::string name, std::string color, int age);

  const std::string& GetName() const;
  int GetAge() const;

private:
  std::string m_Name;
  std::string m_Color;
  int m_Age;
};
