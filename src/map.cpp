#include <stdexcept>

#include <map.hpp>
#include <region.hpp>

Map::Map(
  const std::vector<Region> regions,
  const std::vector<bool> adjacency
)
: m_Regions(regions),
  m_Adjacency(adjacency)
{
  if (regions.size() * regions.size() != adjacency.size()) {
    throw std::invalid_argument("length of adjacency must be equal to length of regions times two");
  }
}

std::vector<Region>& Map::GetRegions() {
  return m_Regions;
}
