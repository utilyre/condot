#pragma once

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

private:
  std::random_device m_RandDev;
  AssetManager m_Assets;
  Map m_Map;
  std::vector<Player> m_Players;
};
