#pragma once

#include <region.hpp>

class Map {
public:
  Map(size_t numRegions, const Region* regions, const bool* adjacency);
  Map(const Map& map);
  ~Map();

  Region* GetRegions() const;
  size_t GetNumRegions() const;

private:
  size_t m_NumRegions;
  Region* m_Regions;
  bool* m_Adjacency;
};
