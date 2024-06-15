#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <unordered_map>

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
  ShuffleCards();
}

void Game::Start() {
  std::system("clear");

  DealCards();

  while (true /* TODO: !IsOver() */) {
    std::system("clear");

    PlaceBattleMarker();

    while (true /* TODO: !IsBattleOver() */) {
      std::system("clear");

      PrintStatus();
      std::cout << '\n';

      PlayCard();
      NextTurn();
    }
  }
}

void Game::PrintStatus() const {
  std::cout << "Table:\n";
  for (const Player& p : m_Players) {
    std::cout << "> " << p.GetName() << ": ";
    for (const auto& card : p.GetDrawnNormalCards()) {
      std::cout << card->GetName() << ' ';
    }
    std::cout << '\n';
  }

  std::cout << '\n';

  using Regions = std::vector<const Region*>;
  std::unordered_map<const Player*, Regions> playerToRegions(m_Players.size());
  for (const Player& p : m_Players) {
    playerToRegions[&p] = Regions();
  }
  for (const Region& r : m_Map.GetRegions()) {
    const Player* ruler = r.GetRuler();
    if (ruler) {
      playerToRegions[ruler].push_back(&r);
    }
  }

  std::cout << "Map:\n";
  for (const auto& [p, regions] : playerToRegions) {
    std::cout << "> " << p->GetName() << ": ";
    for (const Region* r : regions) {
      std::cout << r->GetName() << ' ';
    }
    std::cout << '\n';
  }

  std::cout << '\n';

  std::cout << "Place: " << m_BattleMarker->GetName() << '\n';
  std::cout << "Cards: ";
  for (const auto& card : GetCurrentPlayer().GetCards()) {
    std::cout << card->GetName() << ' ';
  }
  std::cout << '\n';
}

void Game::PlaceBattleMarker() {
  auto regions = m_Map.GetRegions();
  size_t regionIdx{};

  while (true) {
    std::cout << "Choose a region to start the war in:\n";
    for (size_t i = 0; i < regions.size(); i++) {
      std::cout << "  " << i + 1 << ". " << regions[i].GetName() << '\n';
    }

    std::cout << "\n@" << GetCurrentPlayer().GetName()
      << " [1-" << regions.size() << "]: ";

    std::cin >> regionIdx;
    if (regionIdx == 0 || regionIdx > regions.size()) {
      std::cout << "Error: input out of range\n\n";
      continue;
    }

    break;
  }

  m_BattleMarker = &regions[regionIdx - 1];
}

const Player& Game::GetCurrentPlayer() const {
  return m_Players[m_Turn];
}

size_t Game::FindWarInstigator() const {
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

void Game::InsertCards(){
  for(size_t i{1}; i < 11; i++){
    for(size_t j{}; j < 10; j++){
      if( i == 7 || i == 8 || i == 9){
        break;
      }
      else if( i != 1 && j > 7){
        break;
      }
      std::unique_ptr<Card> card = std::make_unique<NormalCard>(i);
      m_Cards.push_back(std::move(card));
    }
  }
}

void Game::ShuffleCards(){
  std::default_random_engine rng(m_RandDev());
  std::shuffle(m_Cards.begin(), m_Cards.end(), rng);
}

void Game::DealCards(){
  for(auto& player : m_Players){
    for(size_t i{}; i < 10; i++){
      player.AddCard(std::move(m_Cards.back()));
      m_Cards.pop_back();
    }
  }
}

std::vector<Player>& Game::GetPlayer() {
  return m_Players;
}

void Game::PlayCard(){
  Player& player = m_Players[m_Turn];

  while (true) {
    std::cout << "@" << player.GetName() << ": ";
    std::string cardname;
    std::cin >> cardname;

    std::unique_ptr<Card> card = player.TakeCard(cardname);
    if (!card) {
      std::cout << "Error: invalid region name\n\n";
      continue;
    }

    std::unique_ptr<NormalCard> ncard(dynamic_cast<NormalCard*>(card.release()));
    if (ncard) {
      player.AddDrawnNormalCard(std::move(ncard));
    }

    // TODO: do something with special cards

    break;
  };
}

void Game::NextTurn() {
  m_Turn = (m_Turn + 1) % m_Players.size();
}
