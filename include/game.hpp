#pragma once

#include <vector>

#include <turn.hpp>
#include <player.hpp>
#include <map.hpp>
#include <region.hpp>
#include <battle.hpp>

class Game {
public:
  Game(std::vector<Player>&& players);

  void Start();

private:
  std::vector<Player> m_Players;
  Turn m_Turn;
  const Map m_Map;
};
