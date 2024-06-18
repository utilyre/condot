#include <cstdio>
#include <iostream>
#include <sstream>
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
: m_Map({
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
  }),
  m_BattleMarker(nullptr),
  m_Players(std::move(players))
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

    do {
      std::system("clear");

      PrintStatus();
      std::cout << '\n';

      PlayCard();
    } while (NextTurn());

    DetermineBattleWinner();
    ResetBattle();
  }
}

void Game::DetermineBattleWinner()
{
  int max_strength = 0;
  std::vector<size_t> potentialWinners;
  for (size_t i = 0; i < m_Players.size(); i++) {
    int strength = m_Players[i].GetStrength();
    if (strength > max_strength) {
      max_strength = strength;
      potentialWinners.clear();
      potentialWinners.push_back(i);
    } else if (strength == max_strength) {
      potentialWinners.push_back(i);
    }
  }

  if (potentialWinners.size() == 1) {
    m_BattleMarker->SetRuler(&m_Players[potentialWinners[0]]);
  }

  std::mt19937 mt(m_RandDev());
  std::uniform_int_distribution<size_t> dist(0, potentialWinners.size() - 1);
  m_Turn = potentialWinners[dist(mt)];
}

void Game::PrintStatus() const {
  std::cout << "Table:\n";
  for (const Player& p : m_Players) {
    std::cout << "> " << p.GetName() << ": ";
    for (const auto& card : p.GetDrawnNormalCards()) {
      std::cout << card->GetName() << ' ';
    }
    if (p.IsPassed()) {
      std::cout << "(passed)";
    }
    else if(p.GetCards().size() == 0){
      std::cout << "(No card to play)\n";
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
  std::cout << '@' << GetCurrentPlayer().GetName() << ": press enter to reveal your cards";
  getchar();
  getchar();
  std::cout << "Cards: ";
    for (const auto& card : GetCurrentPlayer().GetCards()) {
      std::cout << card->GetName() << ' ';
    }
  std::cout << '\n';
}

void Game::PlaceBattleMarker() {
  const auto& regions = m_Map.GetRegions();
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

  m_BattleMarker = m_Map.GetRegion(regionIdx - 1);
}

const Player& Game::GetCurrentPlayer() const {
  return m_Players[m_Turn];
}

size_t Game::FindWarInstigator() {
  int min = INT_MAX;
  std::vector<size_t> potentialInstigators;
  for(size_t i = 0; i < m_Players.size() ; i++){
    int age = m_Players[i].GetAge();
    if (age < min) {
      min = age;
      potentialInstigators.clear();
    } else if (age == min) {
      potentialInstigators.push_back(i);
    }
  }

  std::mt19937 mt(m_RandDev());
  std::uniform_int_distribution<size_t> dist(0, potentialInstigators.size() - 1);
  return potentialInstigators[dist(mt)];
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

static std::vector<std::string> strsplit(const std::string& str, char delim) {
  std::string s;
  std::stringstream ss(str);
  std::vector<std::string> v;
   while (getline(ss, s, delim)) {
    v.push_back(s);
  }
  return v;
}

static std::unordered_map<std::string, std::string> CardHelpMenu{
  {"bishop", "Discard all copies of the highest-value mercenary in play. Place the favor marker in an empty region."},
  {"scarecrow", "Take 1 mercenary from your row back to your hand."},
  {"turncoat", "The battle ends immediately with the winner determined as normal."},
  {"winter", "The value of each mercenary in play is “1.” This card replaces the current season."},
  {"spring", "Add “3” to all copies of the highest value mercenary in play. This card replaces the current season."},
  {"drummer", "Double the value of each mercenary in your row."},
  {"spy", "Add 1 to your strength. At the end of the battle, the player with the most Spies takes the battle marker."},
  {"heroine", "Add 10 to your strength."},
};

void Game::PlayCard(){
  Player& player = m_Players[m_Turn];
  while (true) {
    std::cout << "@" << player.GetName() << ": ";

    std::string input;
    std::getline(std::cin, input);
    if (input == "pass") {
      player.Pass();
      break;
    }

    if (input == "help") {
      for (const auto& [card, desc] : CardHelpMenu) {
        std::cout << card << ": " << desc << '\n';
      }
      std::cout << '\n';

      continue;
    }

    auto words = strsplit(input, ' ');
    if (words.size() == 2 && words[0] == "help") {
      if (CardHelpMenu.count(words[1])) {
        std::cout << CardHelpMenu[words[1]] << "\n\n";
      } else {
        std::cout << "Error: card not found\n\n";
      }

      continue;
    }

    std::unique_ptr<Card> card = player.TakeCard(input);
    if (!card) {
      std::cout << "Error: invalid card name\n\n";
      continue;
    }

    Card* cardPtr = card.release();

    std::unique_ptr<NormalCard> ncard(dynamic_cast<NormalCard*>(cardPtr));
    // TODO: std::unique_ptr<SpecialCard> scard(dynamic_cast<SpecialCard*>(cardPtr));
    if (ncard) {
      player.AddDrawnNormalCard(std::move(ncard));
    // TODO: } else if (scard) {
    } else {
      // in case both casts fail
      delete cardPtr;
    }

    // TODO: do something with special cards

    break;
  };

  if (player.GetCards().empty()) {
    player.Pass();
  }
}

bool Game::NextTurn() {
  size_t initialTurn = m_Turn;

  do {
    m_Turn = (m_Turn + 1) % m_Players.size();
    if (GetCurrentPlayer().IsPassed() && initialTurn == m_Turn) {
      return false;
    }
  } while (GetCurrentPlayer().IsPassed());

  return true;
}

void Game::ResetBattle(){
  for(auto& p : m_Players){
    p.ResetPassed();
    p.ResetDrawnCards();
  }
}
