#include <stdexcept>
#include <unordered_map>
#include <vector>

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
  std::vector<size_t> Idxs;
  std::unordered_map<const Player*, int> numConquered;  
  for (const auto& region : m_Regions) {
    const Player* ruler = region.GetRuler();
    if (ruler) {
      Idxs.push_back(GetIdx(region));
      numConquered[ruler]++;
    }
  }
  
  std::vector<const Player*> winners;
  for (const auto& [player, num] : numConquered) {
    if(num == 3 && AreNeighbors(Idxs[0],Idxs[1]) && AreNeighbors(Idxs[1],Idxs[2]) && AreNeighbors( Idxs[2],Idxs[0])){
      winners.push_back(player);
      break;
    }
    else if (num == 5) {
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
