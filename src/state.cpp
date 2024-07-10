#include <state.hpp>

State::State()
: m_Curr(PLACING_BATTLE_MARKER), // TODO: should be MENU
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
}
