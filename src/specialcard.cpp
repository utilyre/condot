#include <specialcard.hpp>

SpecialCard::SpecialCard(std::string name) : m_Name(name) {}

std::string SpecialCard::GetName() const{
  return m_Name;
}
