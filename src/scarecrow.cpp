#include <raylib.h>

#include <asset_manager.hpp>
#include <scarecrow.hpp>

Texture2D Scarecrow::GetAsset(const AssetManager& assets) const
{
  return assets.Scarecrow;
}
