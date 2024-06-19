#pragma once

#include <cstddef>
#include <vector>

#include <region.hpp>
#include <player.hpp>

class Map {
public:
  Map(std::vector<Region>&& regions, std::vector<bool>&& adjacency);

  const std::vector<Region>& GetRegions() const;
  Region* GetRegion(size_t idx);
  std::vector<const Player*> FindWinners() const;
  
private:
  bool AreNeighbors(size_t i, size_t j) const;
  size_t GetIdx(Region) const ;
private:
  std::vector<Region> m_Regions;
  std::vector<bool> m_Adjacency;
};
