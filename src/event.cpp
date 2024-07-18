#include <memory>
#include <stdexcept>
#include <utility>

#include <event.hpp>

void Event::RegisterListener(std::unique_ptr<EventListener>&& listener)
{
  if (!listener)
  {
    throw std::invalid_argument("argument 'listener' cannot be nullptr");
  }

  for (const auto& l : m_Listeners)
  {
    if (l == listener)
    {
      throw std::logic_error("duplicated listener");
    }
  }

  m_Listeners.push_back(std::move(listener));
}

void Event::UnregisterListener(std::unique_ptr<EventListener>&& listener) noexcept
{
  if (!listener)
  {
    return;
  }

  for (auto it = m_Listeners.begin(); it != m_Listeners.end(); ++it)
  {
    if (*it == listener)
    {
      it = m_Listeners.erase(it);
      return;
    }
  }
}

void Event::Raise(Entity* sender, std::any data)
{
  for (auto& l : m_Listeners)
  {
    l->OnEventRaised(sender, data);
  }
}
