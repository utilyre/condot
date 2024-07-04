#include <raylib.h>

#include <asset_manager.hpp>

void AssetManager::Load()
{
  Map = LoadTexture("assets/map.png");
}

AssetManager::~AssetManager()
{
  UnloadTexture(Map);
}
