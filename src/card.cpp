#include <string>

#include <card.hpp>

Card::Card(const std::string& name)
: m_Name(name)
{
}

const std::string& Card::GetName() const
{
  return m_Name;
}
