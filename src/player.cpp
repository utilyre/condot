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

std::vector<std::shared_ptr<Cards>>& Player::GetAvailableCards() /* cant bind const to address*/
{
  return AvailableCards;
}

void Player::PrintCards(){
  for(auto& card : AvailableCards){
    if(auto* CardPtr = dynamic_cast<NormalCards*>(card.get())){
      std::cout << CardPtr->getPower() << ' ';
    }
  }
}

void Player::PlayCard(std::string cardname){
  for(size_t i{}; i < AvailableCards.size(); i++){
    if(auto* cptr = dynamic_cast<NormalCards*>(AvailableCards[i].get())){
      if(cardname == cptr->GetName()){
        PlayedCards.push_back(std::move(AvailableCards[i]));
        AvailableCards.erase(AvailableCards.begin() + i);
        //std::cout << "size: " << PlayedCards.size() << '\n' << PlayedCards[0]->GetName();
        break;
      }
      else{
        std::cout << cptr->GetName() << " cant delete\n";
      }
    }
    else{
      std::cout << "cant convert\n";
    }
  }
 }

std::vector<std::shared_ptr<Cards>>& Player::GetPlayedCards(){
  return PlayedCards;
}
