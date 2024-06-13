#include <card.hpp>
#include <normalcard.hpp>

NormalCard::NormalCard(int power) : m_Power(power) {}

std::string NormalCard::GetName() const {
  return std::to_string(m_Power);
}
 
int NormalCard::GetPower() const {
  return m_Power;
}
