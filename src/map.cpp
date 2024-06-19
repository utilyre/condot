#include <stdexcept>
#include <unordered_map>
#include <vector>

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

Region* Map::GetRegion(size_t idx) {
  return &m_Regions.at(idx);
}

std::vector<const Player*> Map::FindWinners() const {
  std::unordered_map<const Player*, int> numConquered;  
  for (const auto& region : m_Regions) {
    const Player* ruler = region.GetRuler();
    if (ruler) {
      numConquered[ruler]++;
    }
  }

  std::vector<const Player*> winners;
  for (const auto& [player, num] : numConquered) {
    if (num == 5) {
      winners.push_back(player);
    }
  }

  return winners;
}
