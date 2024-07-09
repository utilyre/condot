#pragma once

#include <raylib.h>

#include <asset_manager.hpp>

struct Card
{
public:
  enum Type {
    MERCENARY_1,
    MERCENARY_2,
    MERCENARY_3,
    MERCENARY_4,
    MERCENARY_5,
    MERCENARY_6,
    MERCENARY_10,

    BISHOP,
    DRUMMER,
    HEROINE,
    SCARECROW,
    SPRING,
    SPY,
    TURNCOAT,
    WINTER,
  };

public:
  Card(Type type);
  Texture2D GetAsset(const AssetManager& assets) const;

public:
  Type type;
};
