#pragma once

#include <any>
#include <vector>
#include <memory>
#include <functional>

#include <entity.hpp>

class EventListener
{
public:
  virtual ~EventListener() {}
  virtual void OnEventRaised(Entity* sender, std::any data) = 0;
};

using EventListenerFunc = std::function<void (Entity* sender, std::any data)>;

class Event
{
public:
  void Register(std::unique_ptr<EventListener>&& listener); // TODO: rename to Subscribe
  void Register(EventListenerFunc listener); // TODO: rename to Subscribe

  void Raise(Entity* sender, std::any data = nullptr);

private:
  std::vector<std::unique_ptr<EventListener>> m_Listeners;
};
