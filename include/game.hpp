#pragma once

#include "normalcards.hpp"
#include <vector>
#include <memory>

#include <player.hpp>
#include <map.hpp>
#include <region.hpp>
#include <cards.hpp>

struct Battle {
  Battle(Region* region) : m_Region(region) {}
  Region* m_Region;
};

class Game {
public:
  Game(std::vector<Player>&& players);
  void  Start();
  const std::vector<std::unique_ptr<Cards>>& GetCards();
private:
  size_t FindWarInstigator() const;
  const Player& GetCurrentPlayer() const;
  Battle InitiateBattle() const;
  std::vector<std::unique_ptr<Cards>>& InsertCards() ;
  std::vector<std::unique_ptr<Cards>>& ShuffleCards();
  void DealTheCards();
private:
  size_t m_Turn;
  std::vector<Player> m_Players;
  std::vector<std::unique_ptr<Cards>> m_Cards;
  Map m_Map;
};
