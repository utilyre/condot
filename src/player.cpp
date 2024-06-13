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
  for(auto* card : m_Cards){
    delete card;
    m_Cards.clear();
  }
}

void Player::AddCard(Card* card)
{
  m_Cards.push_back(card);
}

Card* Player::TakeCard(const std::string& name)
{
  for (auto it = m_Cards.begin(); it != m_Cards.end(); ++it) {
    Card* card = *it;
    if (card->GetName() == name) {
      it = m_Cards.erase(it);
      return card;
    }
  }

  return nullptr;
}

void Player::PrintCards(){
  for(auto& card : m_Cards){
    if(auto* CardPtr = dynamic_cast<NormalCard*>(card)){
      std::cout << CardPtr->GetPower() << ' ';
    }
  }
}
