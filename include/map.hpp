#pragma once

#include <vector>
#include <raylib.h>

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
  std::vector<const Player*> FindWinners() const;
  Region* GetBattleMarker();

private:
  bool AreNeighbors(size_t i, size_t j) const;
  bool AreNeighbors(size_t i, size_t j, size_t k) const;

private:
  State* m_State;
  std::vector<Region> m_Regions;
  std::vector<bool> m_Adjacency;
  Region* m_BattleMarker;
  Region* m_FavorMarker;
};
