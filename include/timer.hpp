#pragma once

class Timer
{
public:
  Timer(float duration, bool repeat = false);

  bool Finished() const;
  void Tick(float dt);

private:
  float m_Duration;
  bool m_Repeat;

  float m_Elapsed;
  bool m_Finished;
};
