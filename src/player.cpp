#include <stdexcept>
#include <iostream>

#include <player.hpp>
#include <normalcard.hpp>

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
  for(auto* card : m_AvailableCards){
    delete card;
    m_AvailableCards.clear();
  }
}

std::vector<Card*>& Player::GetAvailableCards() /* cant bind const to address*/
{
  return m_AvailableCards;
}

Card* Player::TakeAvailableCard(const std::string& name)
{
  for (auto it = m_AvailableCards.begin(); it != m_AvailableCards.end(); ++it) {
    Card* card = *it;
    if (card->GetName() == name) {
      it = m_AvailableCards.erase(it);
      return card;
    }
  }

  return nullptr;
}

void Player::PrintCards(){
  for(auto& card : m_AvailableCards){
    if(auto* CardPtr = dynamic_cast<NormalCard*>(card)){
      std::cout << CardPtr->GetPower() << ' ';
    }
  }
}

std::vector<Card*>& Player::GetPlayedCards(){
  return m_PlayedCards;
}
