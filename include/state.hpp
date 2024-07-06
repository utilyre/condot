#pragma once

class State
{
public:
  State();

  bool IsMenu() const;
  void SetMenu();

  bool IsRegionPick() const;
  void SetRegionPick();

  bool IsPlaying() const;
  void SetPlaying();

private:
  enum {MENU, REGION_PICK, PLAYING} m_Current;
};
