#pragma once

#include "normalcards.hpp"
#include <vector>
#include <memory>

#include <player.hpp>
#include <map.hpp>
#include <region.hpp>
#include <cards.hpp>

struct Battle {
  Battle(Region* region) : m_Region(region) {}
  Region* m_Region;
};

class Game {
public:
  Game(std::vector<Player>&& players);
  ~Game();
  void                       Start();    
  std::vector<Player>&       GetPlayer() ;
  void                       PlayCard();
private:
  size_t                     FindWarInstigator() const;
  const Player&              GetCurrentPlayer() const;
  Battle                     InitiateBattle() const;
  const std::vector<Cards*>& GetCards();
  std::vector<Cards*>&       InsertCards() ;
  std::vector<Cards*>&       ShuffleCards();
  void                       DealTheCards();
private:
  size_t              m_Turn;
  std::vector<Player> m_Players;
  std::vector<Cards*> m_Cards;
  Map                 m_Map;
};
