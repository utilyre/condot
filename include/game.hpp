#pragma once

#include <vector>
#include <random>

#include <asset_manager.hpp>
#include <player.hpp>

class Game
{
public:
  void Start();

private:
  void Update();
  void Render() const;

private:
  std::random_device m_RandDev;
  AssetManager m_Assets;
  std::vector<Player> m_Players;
};
