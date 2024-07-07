#pragma once

#include <memory>
#include <vector>
#include <random>

#include <asset_manager.hpp>
#include <map.hpp>
#include <player.hpp>

class Game
{
public:
  void Start();
  void Menu();
private:
  void Update();
  void Render() const;
  void InsertCards();
  void ShuffleCards();
  void DealCards();
  const Player& GetCurrentPlayer() const;
  size_t FindWarInstigator();
private:
  size_t m_Turn;
  mutable std::random_device m_RandDev;
  AssetManager m_Assets;
  Map m_Map;
  std::vector<Player> m_Players;
  std::vector<std::unique_ptr<Card>> m_Cards;
};
