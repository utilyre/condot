#pragma once

class State
{
public:
  enum Variant {
    MENU,
    PLACING_BATTLE_MARKER,
    PLACING_FAVOR_MARKER,
    PLAYING,
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
