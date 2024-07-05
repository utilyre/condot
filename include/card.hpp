#pragma once

#include <raylib.h>

#include <asset_manager.hpp>

class Card
{
public:
  virtual ~Card() {}
  virtual Texture2D GetAsset(const AssetManager&) const = 0;
};
