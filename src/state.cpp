#include <iostream>

#include <state.hpp>

State::State()
: m_Curr(MAIN_MENU),
  m_Prev(m_Curr)
{
}

State::Variant State::GetPrev() const
{
  return m_Prev;
}

State::Variant State::Get() const
{
  return m_Curr;
}

void State::Set(State::Variant current)
{
  if (current == m_Curr)
  {
    return;
  }

  m_Prev = m_Curr;
  m_Curr = current;
  std::clog << "INFO: state changed from " << m_Prev << " to " << m_Curr << '\n';
}

std::ostream& operator<<(std::ostream& out, State::Variant v)
{
  switch (v)
  {
  case State::MAIN_MENU:
    out << "Menu";
    break;
  case State::PLACING_BATTLE_MARKER:
    out << "Placing Battle Marker";
    break;
  case State::PLACING_FAVOR_MARKER:
    out << "Placing Favor Marker";
    break;
  case State::PLAYING_CARD:
    out << "Playing Card";
    break;
  }

  return out;
}
