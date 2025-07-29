#pragma once

#include <random>
#include <vector>

#include <asset_manager.hpp>
#include <button.hpp>
#include <card.hpp>
#include <customization_menu.hpp>
#include <event.hpp>
#include <help_menu.hpp>
#include <main_menu.hpp>
#include <map.hpp>
#include <pause_menu.hpp>
#include <player.hpp>
#include <season.hpp>
#include <state.hpp>
#include <status_bar.hpp>
#include <stream.hpp>
#include <timer.hpp>

class Game
{
public:
    Game();

    void Start();
    void Stop();

    static void Serialize(StreamWriter& w, const Game& game);
    static void Deserialize(StreamReader& r, Game& game);

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
    void Save();
    void Load();

private:
    bool m_Stopped;

    mutable std::random_device m_RandDev;
    AssetManager m_Assets;

    State m_State;
    size_t m_Turn;
    ssize_t m_FavorMarkerChooserIndex;
    Season m_Season;
    bool m_HideCards;

    Event m_StopEvent;
    Event m_InitiateBattleEvent;
    Event m_RotateTurnEvent;
    Event m_AddPlayerEvent;
    Event m_RestartBattleEvent;
    Event m_SaveEvent;
    Event m_LoadEvent;
    Event m_TakeFavorMarkerEvent;

    Timer m_AutoSaveTimer;

    MainMenu m_MainMenu;
    CustomizationMenu m_CustomizationMenu;
    PauseMenu m_PauseMenu;
    Map m_Map;
    std::vector<Player> m_Players;
    StatusBar m_StatusBar;
    std::vector<Card> m_Deck;
    std::vector<PlayerInfo> m_Winners;
    Button m_ExitButton;
};
