#pragma once

#include <asset_manager.hpp>

class Game
{
public:
  Game();
  ~Game();

  void Start();

private:
  void Update();
  void Render() const;

  int GetWidth() const;
  int GetHeight() const;

private:
  AssetManager m_Assets;
};
