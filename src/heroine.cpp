#include <raylib.h>

#include <heroine.hpp>

Texture2D Heroine::GetAsset(const AssetManager& assets) const{
  return assets.Heroine;
}
