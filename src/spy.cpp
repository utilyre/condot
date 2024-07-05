#include <raylib.h>

#include <asset_manager.hpp>
#include <spy.hpp>

Texture2D Spy::GetAsset(const AssetManager& assets) const
{
  return assets.Spy;
}
