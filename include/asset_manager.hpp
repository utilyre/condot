#pragma once

#include <raylib.h>

struct AssetManager
{
  void Load();
  ~AssetManager();

  Texture2D Map;
};
