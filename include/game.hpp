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

private:
  size_t FindWarInstigator();
  const Player& GetCurrentPlayer() const;
  void PlaceBattleMarker();
  void InsertCards() ;
  void ShuffleCards();
  void DealCards();
  bool NextTurn();
  void PrintStatus() const;
  void DetermineBattleWinner();
  void ResetBattle();
  void PlayCard();
  void IsHandEmpty();

private:
  Map m_Map;
  Region* m_BattleMarker;
  size_t m_Turn;
  std::vector<Player> m_Players;
  std::vector<std::unique_ptr<Card>> m_Cards;

  std::random_device m_RandDev;
};
