#pragma once

class State
{
public:
  State();

  bool IsMenu() const;
  void SetMenu();

  bool IsPlacingBattleMarker() const;
  void SetPlacingBattleMarker();

  bool IsPlacingFavorMarker() const;
  void SetPlacingFavorMarker();

  bool IsPlaying() const;
  void SetPlaying();

private:
  enum {
    MENU,
    PLACING_BATTLE_MARKER,
    PLACING_FAVOR_MARKER,
    PLAYING,
  } m_Current;
};
