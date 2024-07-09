#pragma once

#include <vector>
#include <random>

#include <asset_manager.hpp>
#include <map.hpp>
#include <player.hpp>
#include <card.hpp>

class Game
{
public:
  void Start();

private:
  void Update();
  void Render() const;

  void ResetCards();
  void DealCards();
  const Player& GetCurrentPlayer() const;
  size_t FindWarInstigator();
  // void PlayCard();
  bool NextTurn();

private:
  size_t m_Turn;
  std::random_device m_RandDev;
  AssetManager m_Assets;
  Map m_Map;
  std::vector<Player> m_Players;
  std::vector<Card> m_Cards; // TODO: rename to m_Deck
};
