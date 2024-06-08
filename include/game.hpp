#pragma once

#include <vector>

#include <player.hpp>
#include <map.hpp>
#include <region.hpp>

struct Battle {
  Battle(Region* region) : m_Region(region) {}
  Region* m_Region;
};

class Game {
public:
  Game(std::vector<Player>&& players);

  void Start();

private:
  size_t FindWarInstigator() const;
  const Player& GetCurrentPlayer() const;
  Battle InitiateBattle() const;

private:
  size_t m_Turn;
  std::vector<Player> m_Players;
  Map m_Map;
};
