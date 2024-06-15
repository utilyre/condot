#pragma once

#include <vector>
#include <random>
#include <memory>

#include <player.hpp>
#include <map.hpp>
#include <region.hpp>
#include <card.hpp>

class Game {
public:
  Game(std::vector<Player>&& players);

  void Start();
  std::vector<Player>& GetPlayer() ;
  void PlayCard();

private:
  size_t FindWarInstigator() const;
  const Player& GetCurrentPlayer() const;
  void PlaceBattleMarker();
  void InsertCards() ;
  void ShuffleCards();
  void DealCards();
  void NextTurn();
  void PrintStatus() const;

private:
  size_t m_Turn;
  std::vector<Player> m_Players;
  std::vector<std::unique_ptr<Card>> m_Cards;
  Map m_Map;
  Region* m_BattleMarker;

  std::random_device m_RandDev;
};
