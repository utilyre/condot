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
  std::vector<int> conqured;
  std::unordered_map<const Player*,std::vector<int>> numConquered;  
  for (const auto& region : m_Regions) {
    const Player* ruler = region.GetRuler();
    if (ruler) {
      numConquered[ruler].push_back(GetIdx(region));
      conqured.push_back(GetIdx(region));
    }
  }
  
  std::vector<const Player*> winners;
  for (const auto& [player, conquered] : numConquered) {
    if((conquered.size() == 3 || conquered.size() == 4) && DetermineAdjacency(conqured)){
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

bool Map::DetermineAdjacency(std::vector<int>& size) const{
  std::vector<bool> Neighbors;
  for(size_t i{} ; i < size.size(); i++){
    for(size_t j{}; j < size.size(); j++){
      if(AreNeighbors(size[i], size[j])){
        Neighbors.push_back(1);
      }
    }
  }
  if(Neighbors.size() == 6){
    return true;
  }
  return false;
}
