#pragma once

#include <asset_manager.hpp>

class Drawable
{
  virtual void Draw(AssetManager) const = 0;
};
