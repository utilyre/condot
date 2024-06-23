#include <stdexcept>

#include <player.hpp>
#include <normalcard.hpp>

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

void Player::AddCard(std::unique_ptr<Card>&& card)
{
  m_Cards.push_back(std::move(card));
}

std::unique_ptr<Card> Player::TakeCard(const std::string& name)
{
  for (auto it = m_Cards.begin(); it != m_Cards.end(); ++it) {
    std::unique_ptr<Card>& card = *it;
    if (card->GetName() == name) {
      std::unique_ptr<Card> c = std::move(*it);
      it = m_Cards.erase(it);
      return c;
    }
  }

  return nullptr;
}

void Player::AddDrawnNormalCard(std::unique_ptr<NormalCard>&& card) {
  m_DrawnNormalCards.push_back(std::move(card));
}

const std::vector<std::unique_ptr<Card>>& Player::GetCards() const
{
  return m_Cards;
}

const std::vector<std::unique_ptr<NormalCard>>& Player::GetDrawnNormalCards() const
{
  return m_DrawnNormalCards;
}

void Player::Pass(){
  m_Passed = true;
}

bool Player::IsPassed() const
{
  return m_Passed;
}

int Player::GetStrength() const
{
  int sum = 0;
  for (const auto& card : m_DrawnNormalCards) {
    sum += card->GetPower();
  }
  return sum;
}

void Player::ResetPassed(){
  m_Passed = false;
}

void Player::ResetDrawnCards(){
  m_DrawnNormalCards.clear(); 
}

void Player::ResetCards(){
  m_Cards.clear();
}
