#pragma once

#include <raylib.h>

#include <asset_manager.hpp>

struct Card
{
  enum Type {
    MERCENARY,
    BISHOP,
    DRUMMER,
    HEROINE,
    SCARECROW,
    SPRING,
    SPY,
    TURNCOAT,
    WINTER,
  } type;
  int power; // used only for mercenary type

  Texture2D GetAsset(const AssetManager& assets) const
  {
    switch (type)
    {
    case MERCENARY:
      switch (power)
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
};
