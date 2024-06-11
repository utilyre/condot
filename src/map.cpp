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

const std::vector<Region>& Map::GetRegions() const {
  return m_Regions;
}

const Region* Map::GetRegion(size_t idx) const {
  return &m_Regions.at(idx);
}
