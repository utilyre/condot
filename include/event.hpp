#pragma once

#include <any>
#include <vector>
#include <memory>
#include <functional>

#include <entity.hpp>

class Observer
{
public:
  virtual ~Observer() {}
  virtual void OnNotify(Entity* sender, std::any data) = 0;
};

using ObserverFunc = std::function<void (Entity* sender, std::any data)>;

class Event
{
public:
  void Subscribe(std::unique_ptr<Observer>&& observer);
  void Subscribe(ObserverFunc observer);

  void Notify(Entity* sender, std::any data = nullptr);

private:
  std::vector<std::unique_ptr<Observer>> m_Observers;
};
