#include <raylib.h>

#include <asset_manager.hpp>
#include <turncoat.hpp>

Texture2D Turncoat::GetAsset(const AssetManager& assets) const
{
  return assets.Turncoat;
}
