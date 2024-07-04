#pragma once

#include <asset_manager.hpp>

class Entity
{
public:
  virtual ~Entity() {};

  virtual void Update() = 0;
  virtual void Render(const AssetManager&) const = 0;
};
