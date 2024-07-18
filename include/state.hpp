#pragma once

#include <iostream>

#include <card.hpp>

class State
{
public:
  enum Variant {
    START_MENU,
    PLAYER_PICK_MENU,
    PLACING_BATTLE_MARKER,
    PLACING_FAVOR_MARKER,
    PLAYING_CARD,
    BISHOP,
    SCARECROW
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
