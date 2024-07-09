#include <raylib.h>

#include <asset_manager.hpp>
#include <card.hpp>

Card::Card(Type type) : type(type) {}

Texture2D Card::GetAsset(const AssetManager& assets) const
{
  switch (type)
  {
  case MERCENARY_1:
    return assets.Mercenary01;
  case MERCENARY_2:
    return assets.Mercenary02;
  case MERCENARY_3:
    return assets.Mercenary03;
  case MERCENARY_4:
    return assets.Mercenary04;
  case MERCENARY_5:
    return assets.Mercenary05;
  case MERCENARY_6:
    return assets.Mercenary06;
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

  default:
    return assets.Mercenary01;
  }
}
