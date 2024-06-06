#pragma once

#include <region.hpp>

class Map {
public:
  /**
   * Map constructor takes ownership of regions but not adjacency.
   */
  Map(size_t numRegions, Region* regions, const bool* adjacency);

  Map(const Map& map);
  ~Map();

private:
  size_t m_NumRegions;
  Region* m_Regions;
  const bool* m_Adjacency;
};
