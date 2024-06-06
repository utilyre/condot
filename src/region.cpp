#include <region.hpp>

Region::Region(const std::string& name) : m_Name(name) {}

void Region::SetRuler(const Player* ruler) {
  m_Ruler = ruler;
}

const Player* Region::GetRuler() const {
  return m_Ruler;
}

const std::string& Region::GetName() const {
  return m_Name;
}
