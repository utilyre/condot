#pragma once

#include <vector>
#include <random>

#include <asset_manager.hpp>
#include <state.hpp>
#include <map.hpp>
#include <player.hpp>

class Game
{
public:
  Game();

  void Start();
  void Menu();
private:
  void Update();
  void Render() const;

private:
  mutable std::random_device m_RandDev;
  AssetManager m_Assets;
  State m_State;
  Map m_Map;
  std::vector<Player> m_Players;
};
