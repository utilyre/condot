#include <memory>
#include <stdexcept>
#include <iostream>

#include <player.hpp>
#include <normalcards.hpp>

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

Player::~Player(){
  for(auto* card : AvailableCards){
    delete card;
    AvailableCards.clear();
    //std::cout << " x: card\n";
  }
}

std::vector<Cards*>& Player::GetAvailableCards() /* cant bind const to address*/
{
  return AvailableCards;
}

void Player::PrintCards(){
  for(auto& card : AvailableCards){
    if(auto* CardPtr = dynamic_cast<NormalCards*>(card)){
      std::cout << CardPtr->getPower() << ' ';
    }
  }
}

std::vector<Cards*>& Player::GetPlayedCards(){
  return PlayedCards;
}
