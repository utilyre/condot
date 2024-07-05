#include <raylib.h>

#include <asset_manager.hpp>
#include <drummer.hpp>

Texture2D Drummer::GetAsset(const AssetManager& assets) const
{
  return assets.Drummer;
}
