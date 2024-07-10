#pragma once

#include <iostream>

class State
{
public:
  enum Variant {
    MENU,
    INITIATING_BATTLE,
    PLACING_BATTLE_MARKER,
    PLACING_FAVOR_MARKER,
    PLAYING_CARD,
    ROTATING_TURN,
  };

public:
  State();

  Variant GetPrev() const;
  Variant Get() const;
  void Set(Variant current);

private:
  Variant m_Curr;
  Variant m_Prev;
};

std::ostream& operator<<(std::ostream& out, State::Variant v);
