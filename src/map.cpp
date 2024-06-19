#include <stdexcept>
#include <unordered_map>
#include <vector>
#include <iostream>

#include <map.hpp>
#include <region.hpp>

Map::Map(
  std::vector<Region>&& regions,
  std::vector<bool>&& adjacency
)
: m_Regions(std::move(regions)),
  m_Adjacency(std::move(adjacency))
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
  std::unordered_map<const Player*,std::vector<int>> numConquered;  
  for (const auto& region : m_Regions) {
    const Player* ruler = region.GetRuler();
    if (ruler) {
      numConquered[ruler].push_back(GetIdx(region));
    }
  }
  
  std::vector<const Player*> winners;
  for (const auto& [player, conquered] : numConquered) {
    if(conquered.size() == 3 && AreNeighbors(conquered[0],conquered[1]) && AreNeighbors(conquered[1],conquered[2]) && AreNeighbors(conquered[2],conquered[0])){
      winners.push_back(player);
      break;
    }
    else if (conquered.size() == 5) {
      winners.push_back(player);
    }
  }

  return winners;
}

bool Map::AreNeighbors(size_t i, size_t j) const
{
  return m_Adjacency[m_Regions.size() * i + j];
}

size_t Map::GetIdx(Region region) const {
  for(size_t i{} ; i < GetRegions().size(); i++){
    if(GetRegions()[i].GetName() == region.GetName()){
      return i;
    }
  }
  return 0;
}
