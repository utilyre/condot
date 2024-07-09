#include <raylib.h>

#include <asset_manager.hpp>
#include <mercenary.hpp>

Mercenary::Mercenary(int power)
: m_Power(power)
{
}

Texture2D Mercenary::GetAsset(const AssetManager& assets) const
{
  switch (m_Power)
  {
  case 1:
    return assets.Mercenary1;
  case 2:
    return assets.Mercenary2;
  case 3:
    return assets.Mercenary3;
  case 4:
    return assets.Mercenary4;
  case 5:
    return assets.Mercenary5;
  case 6:
    return assets.Mercenary6;
  case 10:
    return assets.Mercenary10;
  default:
    return assets.Mercenary1;
  }
}

int Mercenary::GetPower() const
{
  return m_Power;
}
