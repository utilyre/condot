#include <raylib.h>

#include <asset_manager.hpp>
#include <bishop.hpp>

Texture2D Bishop::GetAsset(const AssetManager& assets) const
{
  return assets.Bishop;
}
