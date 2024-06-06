#include <map.hpp>
#include <region.hpp>

Map::Map(size_t numRegions, const Region* regions, const bool* adjacency)
: m_NumRegions(numRegions)
{
  m_Regions = new Region[numRegions];
  for (size_t i = 0; i < numRegions; i++) {
    m_Regions[i] = regions[i];
  }

  m_Adjacency = new bool[numRegions * numRegions];
  for (size_t i = 0; i < numRegions * numRegions; i++) {
    m_Adjacency[i] = adjacency[i];
  }
}

Map::Map(const Map& map)
: m_NumRegions(map.m_NumRegions),
  m_Adjacency(map.m_Adjacency)
{
  m_Regions = new Region[map.m_NumRegions];
  for (size_t i = 0; i < m_NumRegions; i++) {
    m_Regions[i] = map.m_Regions[i];
  }

  m_Adjacency = new bool[map.m_NumRegions * map.m_NumRegions];
  for (size_t i = 0; i < map.m_NumRegions * map.m_NumRegions; i++) {
    m_Adjacency[i] = map.m_Adjacency[i];
  }
}

Map::~Map() {
  delete[] m_Adjacency;
  delete[] m_Regions;
}

Region* Map::GetRegions() const {
  return m_Regions;
}

size_t Map::GetNumRegions() const {
  return m_NumRegions;
}
