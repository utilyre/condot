#pragma once

#include <vector>
#include <random>

#include <player.hpp>
#include <map.hpp>
#include <region.hpp>
#include <card.hpp>

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
  void PlaceBattleMarker();
  const std::vector<Card*>& GetCards();
  std::vector<Card*>& InsertCards() ;
  std::vector<Card*>& ShuffleCards();
  void DealTheCards();
  void NextTurn();

private:
  size_t m_Turn;
  std::vector<Player> m_Players;
  std::vector<Card*> m_Cards;
  Map m_Map;
  Region* m_BattleMarker;

  std::random_device m_RandDev;
};
