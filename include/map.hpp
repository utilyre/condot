#pragma once

#include <vector>

#include <asset_manager.hpp>
#include <entity.hpp>
#include <region.hpp>

class Map : public Entity
{
public:
  Map();

  void Update() override;
  void Render(const AssetManager& assets) const override;

private:
  std::vector<Region> m_Regions;
};
