#pragma once

#include <vector>

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
  AssetManager m_Assets;
  std::vector<Player> m_Players;
};
