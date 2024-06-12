#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <random>

#include <card.hpp>
#include <normalcard.hpp>
#include <game.hpp>
#include <player.hpp>
#include <region.hpp>
#include <map.hpp>

Game::Game(std::vector<Player>&& players)
: m_Players(std::move(players)),
  m_Map({
    Region("Bella"),
    Region("Caline"),
    Region("Enna"),
    Region("Atela"),
    Region("Pladaci"),
    Region("Borge"),
    Region("Dimase"),
    Region("Rollo"),
    Region("Mornia"),
    Region("Olivadi"),
    Region("Talmone"),
    Region("Armento"),
    Region("Lia"),
    Region("Elinia"),
  },
  {
    /*                0  1  2  3  4  5  6  7  8  9 10 11 12 13 */
    /*  0: Bella   */ 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /*  1: Caline  */ 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    /*  2: Enna    */ 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0,
    /*  3: Altela  */ 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
    /*  4: Pladaci */ 1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0,
    /*  5: Borge   */ 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0,
    /*  6: Dimase  */ 0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0,
    /*  7: Rollo   */ 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1,
    /*  8: Mornia  */ 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0,
    /*  9: Olivadi */ 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0,
    /* 10: Talmone */ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1,
    /* 11: Armento */ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0,
    /* 12: Lia     */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0,
    /* 13: Elinia  */ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0,
  })
{
  m_Turn = FindWarInstigator();
  InsertCards();
}

Game::~Game(){
  for(auto& card : m_Cards){
    delete card;
    m_Cards.clear();
    //std::cout << "card deleted\n";
   }
 }

void Game::Start() {
  Battle battle = InitiateBattle();
  std::cout << "Starting at " << battle.m_Region->GetName() << '\n';
  DealTheCards();
}

Battle Game::InitiateBattle() const {
  auto regions = m_Map.GetRegions();
  size_t regionIdx{};

  do {
    std::system("clear");

    std::cout << "Choose a region to start the war in:\n";
    for (size_t i = 0; i < regions.size(); i++) {
      std::cout << "  " << i + 1 << ". " << regions[i].GetName() << '\n';
    }

    std::cout << "\n@" << GetCurrentPlayer().GetName()
      << " [1-" << regions.size() << "]: ";

    std::cin >> regionIdx;
  } while (regionIdx == 0 || regionIdx > regions.size());
  return Battle(&regions[regionIdx - 1]);
}

const Player& Game::GetCurrentPlayer() const {
  return m_Players[m_Turn];
}

size_t Game::FindWarInstigator() const {
  void Start();
  int min = m_Players[0].GetAge();
  std::vector<int> potentialInstigators;
  for(size_t i = 0; i < m_Players.size() ; i++){
    if(m_Players[i].GetAge() < min){
      min = m_Players[i].GetAge();
      potentialInstigators.clear();
    }

    if(m_Players[i].GetAge() == min){
      potentialInstigators.push_back(i);
    }
  }

  size_t randNum = rand() % potentialInstigators.size();
  return potentialInstigators[randNum];
}

std::vector<Card*>& Game::InsertCards(){
  for(size_t i{1}; i < 11; i++){
    for(size_t j{}; j < 10; j++){
      if( i == 7 || i == 8 || i == 9){
        break;
      }
      else if( i != 1 && j > 7){
        break;
      }
      NormalCard* card = new NormalCard(i);
      m_Cards.push_back(card);
    }
  }
  ShuffleCards();
  return m_Cards;
}

const std::vector<Card*>& Game::GetCards(){
  return m_Cards;
}

std::vector<Card*>& Game::ShuffleCards(){
  int seed = rand();
  std::shuffle(m_Cards.begin(), m_Cards.end(), std::default_random_engine(seed));
  return m_Cards;  
}

void Game::DealTheCards(){
  for(auto& player : m_Players){
    for(size_t i{}; i < 10; i++){
      player.GetAvailableCards().push_back(m_Cards.back());
      m_Cards.pop_back();
    }
  }
}

std::vector<Player>& Game::GetPlayer() {
  return m_Players;
}

void Game::PlayCard(){
  for(auto& player : m_Players){
    system("clear");

    std::cout << "Available Cards:\n";
    player.PrintCards();

    std::cout << "\n\n@" << player.GetName() << ": ";
    std::string cardname;
    std::cin >> cardname;

    for(size_t i{}; i < player.GetAvailableCards().size(); i++){
      Card* card = player.GetAvailableCards()[i];
      if (card->GetName() == cardname) {
        player.GetPlayedCards().push_back(player.GetAvailableCards()[i]);
        player.GetAvailableCards().erase(player.GetAvailableCards().begin() + i);
        break;
      }
    }
  }  
}
