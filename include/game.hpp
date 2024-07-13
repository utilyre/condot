#pragma once

#include <vector>
#include <random>

#include <asset_manager.hpp>
#include <state.hpp>
#include <map.hpp>
#include <player.hpp>
#include <card.hpp>
#include <menu.hpp>

class Game
{
public:
  Game();

  void Start();
  void Stop();

private:
  void Update();
  void Render() const;

  const Player& GetCurrentPlayer() const;
  size_t FindBattleInstigatorIndex() const;
  void ResetCards();
  void DealCards();
  void InitiateBattle();
  bool NextTurn();

private:
  bool m_Stopped;
  size_t m_Turn;
  mutable std::random_device m_RandDev;
  AssetManager m_Assets;
  State m_State;
  StartMenu m_StartMenu;
  Map m_Map;
  std::vector<Player> m_Players;
  std::vector<Card> m_Deck;
};
