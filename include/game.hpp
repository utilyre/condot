#pragma once

#include <vector>

#include <player.hpp>
#include <map.hpp>
#include <region.hpp>
#include <card.hpp>

struct Battle {
  Battle(Region* region) : m_Region(region) {}
  Region* m_Region;
};

class Game {
public:
  Game(std::vector<Player>&& players);
  ~Game();
  void Start();
  std::vector<Player>& GetPlayer() ;
  void PlayCard();

private:
  size_t FindWarInstigator() const;
  Player& GetCurrentPlayer();
  Battle InitiateBattle();
  const std::vector<Card*>& GetCards();
  std::vector<Card*>& InsertCards() ;
  std::vector<Card*>& ShuffleCards();
  void DealTheCards();

private:
  size_t m_Turn;
  std::vector<Player> m_Players;
  std::vector<Card*> m_Cards;
  Map m_Map;
};
