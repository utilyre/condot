#include <raylib.h>

#include <asset_manager.hpp>
#include <map.hpp>

void Map::Update()
{
}

void Map::Render(const AssetManager& assets) const
{
  int width = GetScreenWidth();
  int height = GetScreenHeight();

  DrawTexture(assets.Map, (width - assets.Map.width) / 2, (height - assets.Map.height) / 2, WHITE);
}
