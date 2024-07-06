#include <state.hpp>

State::State()
: m_Current(PLACING_BATTLE_MARKER) // TODO: should be MENU
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

bool State::IsPlacingBattleMarker() const
{
  return m_Current == PLACING_BATTLE_MARKER;
}

void State::SetPlacingBattleMarker()
{
  m_Current = PLACING_BATTLE_MARKER;
}

bool State::IsPlacingFavorMarker() const
{
  return m_Current == PLACING_FAVOR_MARKER;
}

void State::SetPlacingFavorMarker()
{
  m_Current = PLACING_FAVOR_MARKER;
}

bool State::IsPlaying() const
{
  return m_Current == PLAYING;
}

void State::SetPlaying()
{
  m_Current = PLAYING;
}
