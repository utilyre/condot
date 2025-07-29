#pragma once

#include <csetjmp>
#include <iostream>

#include <card.hpp>

class State
{
public:
  enum Variant {
    MAIN_MENU,
    CUSTOMIZATION_MENU,
    PLACING_BATTLE_MARKER,
    PLACING_FAVOR_MARKER,
    PLAYING_CARD,
    PAUSE_MENU,
    SCARECROW,
    SHOW_WINNER_PLAYER,
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
