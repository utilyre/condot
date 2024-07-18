#include <memory>
#include <stdexcept>
#include <utility>

#include <event.hpp>

void Event::Register(std::unique_ptr<EventListener>&& listener)
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

class LambdaEventListener : public EventListener
{
public:
  LambdaEventListener(EventListenerFunc func) : m_Func(func) {}

  void OnEventRaised(Entity* sender, std::any data) override
  {
    m_Func(sender, data);
  }

private:
  std::function<void (Entity* sender, std::any data)> m_Func;
};

void Event::Register(EventListenerFunc listener)
{
  if (!listener)
  {
    throw std::invalid_argument("argument 'listener' cannot be nullptr");
  }

  Register(std::make_unique<LambdaEventListener>(listener));
}

void Event::Raise(Entity* sender, std::any data)
{
  for (auto& l : m_Listeners)
  {
    l->OnEventRaised(sender, data);
  }
}
