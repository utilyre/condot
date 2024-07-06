#pragma once

#include <vector>

#include <asset_manager.hpp>
#include <state.hpp>
#include <entity.hpp>
#include <region.hpp>

class Map : public Entity
{
public:
  Map(State* state);

  void Update() override;
  void Render(const AssetManager& assets) const override;

private:
  State* m_State;
  std::vector<Region> m_Regions;
};
