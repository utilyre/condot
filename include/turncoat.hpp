#pragma once

#include <raylib.h>

#include <asset_manager.hpp>
#include <card.hpp>

class Turncoat : public Card
{
public:
  Texture2D GetAsset(const AssetManager& assets) const override;

private:
};
