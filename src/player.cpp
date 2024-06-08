#include <stdexcept>

#include <player.hpp>

Player::Player() : m_Age(0) {}

Player::Player(std::string name, std::string color, int age)
: m_Name(name),
  m_Color(color),
  m_Age(age)
{
  if (age < 0) {
    throw std::invalid_argument("age cannot be negative");
  }
}

const std::string& Player::GetName() const {
  return m_Name;
}

int Player::GetAge() const {
  return m_Age;
}
