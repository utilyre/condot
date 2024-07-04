#pragma once

#include <asset_manager.hpp>

class Drawable
{
  virtual void Draw(const AssetManager&) const = 0;
};
