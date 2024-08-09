#include <timer.hpp>

Timer::Timer(float duration, bool repeat)
: m_Duration(duration),
  m_Repeat(repeat),
  m_Elapsed(0.0f),
  m_Finished(false)
{
}

bool Timer::Finished() const
{
  return m_Finished;
}

void Timer::Tick(float dt)
{
  m_Elapsed += dt;
  m_Finished = m_Elapsed >= m_Duration;

  if (m_Finished)
  {
    m_Elapsed = m_Repeat ? 0.0f : m_Duration;
  }
}
