#pragma once

#include <asset_manager.hpp>
#include <entity.hpp>

class Map : public Entity
{
public:
  void Update() override;
  void Render(const AssetManager& assets) const override;

private:
};
