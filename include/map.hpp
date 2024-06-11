#pragma once

#include <vector>

#include <region.hpp>

class Map {
public:
  Map(const std::vector<Region> regions, const std::vector<bool> adjacency);

  std::vector<Region>& GetRegions();

private:
  std::vector<Region> m_Regions;
  std::vector<bool> m_Adjacency;
};
