#pragma once

#include <vector>

#include <region.hpp>

class Map {
public:
  Map(const std::vector<Region> regions, const std::vector<bool> adjacency);

  const std::vector<Region>& GetRegions() const;
  Region* GetRegion(size_t idx);

private:
  std::vector<Region> m_Regions;
  std::vector<bool> m_Adjacency;
};
