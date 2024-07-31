#include <iostream>

#include <state.hpp>

State::State()
: m_Curr(MAIN_MENU),
  m_Prev(m_Curr),
  m_Season(NONE)
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

State::Season State::GetSeason() const
{
  return m_Season;
}

void State::Set(Season current)
{
  m_Season = current;
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
    out << "MAIN_MENU";
    break;
  case State::CUSTOMIZATION_MENU:
    out << "CUSTOMIZATION_MENU";
    break;
  case State::PLACING_BATTLE_MARKER:
    out << "PLACING_BATTLE_MARKER";
    break;
  case State::PLACING_FAVOR_MARKER:
    out << "PLACING_FAVOR_MARKER";
    break;
  case State::PLAYING_CARD:
    out << "PLAYING_CARD";
    break;
  case State::SCARECROW:
    out << "SCARECROW";
  }

  return out;
}
