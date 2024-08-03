#include <memory>
#include <stdexcept>
#include <utility>

#include <event.hpp>

void Event::Subscribe(std::unique_ptr<Observer>&& observer)
{
  if (!observer)
  {
    throw std::invalid_argument("argument 'observer' cannot be nullptr");
  }

  for (const auto& l : m_Observers)
  {
    if (l == observer)
    {
      throw std::logic_error("duplicated observer");
    }
  }

  m_Observers.push_back(std::move(observer));
}

class LambdaObserver : public Observer
{
public:
  LambdaObserver(ObserverFunc func) : m_Func(func) {}

  void OnNotify(Entity* sender, std::any data) override
  {
    m_Func(sender, data);
  }

private:
  std::function<void (Entity* sender, std::any data)> m_Func;
};

void Event::Subscribe(ObserverFunc observer)
{
  if (!observer)
  {
    throw std::invalid_argument("argument 'observer' cannot be nullptr");
  }

  Subscribe(std::make_unique<LambdaObserver>(observer));
}

void Event::Notify(Entity* sender, std::any data)
{
  for (auto& l : m_Observers)
  {
    l->OnEventRaised(sender, data);
  }
}
