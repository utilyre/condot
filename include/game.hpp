#pragma once

#include <vector>
#include <string>

#include <player.hpp>
#include <map.hpp>

class Game {
public:
  Game(const std::vector<Player>& players, const Map& map);

  const Player& GetCurrentPlayer() const;
  void setBattleMarker(std::string battleMarkerValue);
  const std::string getBattleMarker() const;

private:
  size_t FindWarInstigator() const;

private:
  size_t m_Turn = 0;
  std::vector<Player> m_Players;
  Map m_Map;
  std::string battleMarker; // TODO: set this field after determining the city
};
