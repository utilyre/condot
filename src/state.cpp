#include <state.hpp>

State::State()
: m_Current(REGION_PICK) // TODO: should be MENU
{
}

bool State::IsMenu() const
{
  return m_Current == MENU;
}

void State::SetMenu()
{
  m_Current = MENU;
}

bool State::IsRegionPick() const
{
  return m_Current == REGION_PICK;
}

void State::SetRegionPick()
{
  m_Current = REGION_PICK;
}

bool State::IsPlaying() const
{
  return m_Current == PLAYING;
}

void State::SetPlaying()
{
  m_Current = PLAYING;
}
