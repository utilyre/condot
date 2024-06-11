#pragma once

#include <region.hpp>
#include <map.hpp>
#include <turn.hpp>

enum class Season {
  None,
  Winter,
  Spring,
};

class Battle {
public:
  Battle(Turn* turn, const Map* map);

  void Start();

private:
  void SelectRegion();

private:
  Turn* m_Turn;
  const Map* m_Map;
  const Region* m_Region;
  Season m_Season;
};
