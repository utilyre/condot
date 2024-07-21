#include <raylib.h>

#include <asset_manager.hpp>
#include <card.hpp>

Card::Card(Type type) : m_Type(type) {}

Card::Type Card::GetType() const
{
  return m_Type;
}

Texture2D Card::GetAsset(const AssetManager& assets) const
{
  switch (m_Type)
  {
  case MERCENARY_1:
    return assets.Mercenary1;
  case MERCENARY_2:
    return assets.Mercenary2;
  case MERCENARY_3:
    return assets.Mercenary3;
  case MERCENARY_4:
    return assets.Mercenary4;
  case MERCENARY_5:
    return assets.Mercenary5;
  case MERCENARY_6:
    return assets.Mercenary6;
  case MERCENARY_10:
    return assets.Mercenary10;

  case BISHOP:
    return assets.Bishop;
  case DRUMMER:
    return assets.Drummer;
  case HEROINE:
    return assets.Heroine;
  case SCARECROW:
    return assets.Scarecrow;
  case SPRING:
    return assets.Spring;
  case SPY:
    return assets.Spy;
  case TURNCOAT:
    return assets.Turncoat;
  case WINTER:
    return assets.Winter;
  case BACKSIDE:
    return assets.BackSide;

  default:
    return assets.Mercenary1;
  }
}
