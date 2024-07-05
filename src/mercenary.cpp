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
    return assets.Mercenary01;
  case 2:
    return assets.Mercenary02;
  case 3:
    return assets.Mercenary03;
  case 4:
    return assets.Mercenary04;
  case 5:
    return assets.Mercenary05;
  case 6:
    return assets.Mercenary06;
  case 10:
    return assets.Mercenary10;
  default:
    return assets.Mercenary01;
  }
}

int Mercenary::GetPower() const
{
  return m_Power;
}
