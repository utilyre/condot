#pragma once

#include <any>
#include <vector>
#include <memory>

#include <entity.hpp>

class EventListener
{
public:
  virtual ~EventListener() {}
  virtual void OnEventRaised(Entity* sender, std::any data) = 0;
};

class Event
{
public:
  void Register(std::unique_ptr<EventListener>&& listener);
  void Unregister(std::unique_ptr<EventListener>&& listener) noexcept;

  void Raise(Entity* sender, std::any data);

private:
  std::vector<std::unique_ptr<EventListener>> m_Listeners;
};
