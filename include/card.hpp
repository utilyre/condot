#pragma once

#include <raylib.h>

#include <asset_manager.hpp>

class Card
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

  Type GetType() const;
  Texture2D GetAsset(const AssetManager& assets) const;

private:
  Type m_Type;
};
