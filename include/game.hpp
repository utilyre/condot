#pragma once

#include <vector>
#include <random>

#include <asset_manager.hpp>
#include <event.hpp>
#include <state.hpp>
#include <map.hpp>
#include <player.hpp>
#include <card.hpp>
#include <main_menu.hpp>
#include <customization_menu.hpp>
#include <season.hpp>
#include <stream.hpp>

class Game
{
public:
  Game();

  void Start();
  void Stop();

  static bool Serialize(StreamWriter& w, const Game& game);
  static bool Deserialize(StreamReader& r, Game& game);

private:
  void Update();
  void Render() const;

  size_t FindBattleInstigatorIndex() const;
  void ResetCards();
  void DealCards();
  void InitiateBattle();
  void RotateTurn(bool* Status);
  void PickCard();
  void FindRegionConquerer();
  void FixPosition();
  void RestartBattle();

private:
  bool m_Stopped;

  mutable std::random_device m_RandDev;
  AssetManager m_Assets;

  State m_State;
  size_t m_Turn;
  Season m_Season;

  Event m_StopEvent;
  Event m_InitiateBattleEvent;
  Event m_RotateTurnEvent;
  Event m_AddPlayerEvent;
  Event m_RestartBattleEvent;

  MainMenu m_MainMenu;
  CustomizationMenu m_CustomizationMenu;
  Map m_Map;
  std::vector<Player> m_Players;
  std::vector<Card> m_Deck;
};
