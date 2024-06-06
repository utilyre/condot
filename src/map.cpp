#include <map.hpp>
#include <region.hpp>

Map::Map(size_t numRegions, Region* regions, const bool* adjacency)
: m_NumRegions(numRegions),
  m_Regions(regions),
  m_Adjacency(adjacency)
{}

Map::Map(const Map& map)
: m_NumRegions(map.m_NumRegions),
  m_Adjacency(map.m_Adjacency)
{
  for (size_t i = 0; i < m_NumRegions; i++) {
    m_Regions[i] = map.m_Regions[i];
  }
}

Map::~Map() {
  delete[] m_Regions;
}
