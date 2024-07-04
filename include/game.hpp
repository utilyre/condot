#pragma once

#include <asset_manager.hpp>

class Game
{
public:
  void Start();

private:
  void Update();
  void Render() const;

private:
  AssetManager m_Assets;
};
