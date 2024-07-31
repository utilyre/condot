#pragma once

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
    SCARECROW,
  };

  enum Season {
    NONE,
    SPRING,
    WINTER,
  };
  
public:
  State();

  Variant GetPrev() const;
  Variant Get() const;
  Season GetSeason() const;
  void Set(Season current);
  void Set(Variant current);

private:
  Variant m_Curr;
  Variant m_Prev;
  Season m_Season;
};

std::ostream& operator<<(std::ostream& out, State::Variant v);
