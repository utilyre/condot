#include <iostream>

#include <game.hpp>
#include <player.hpp>
#include <region.hpp>
#include <map.hpp>

Game::Game(
  const std::vector<Player>& players,
  const Map& map
)
: m_Players(players),
  m_Map(map)
{
  m_Turn = FindWarInstigator();
}

void Game::Start() {
  Battle battle = InitiateBattle();
  std::cout << "Starting at " << battle.m_Region->GetName() << '\n';
}

Battle Game::InitiateBattle() const {
  auto regions = m_Map.GetRegions();
  size_t regionIdx;

  do {
    std::system("clear");

    std::cout << "Choose a region to start the war in:\n";
    for (size_t i = 0; i < regions.size(); i++) {
      std::cout << "  " << i + 1 << ". " << regions[i].GetName() << '\n';
    }

    std::cout << "\n@" << GetCurrentPlayer().name
      << " [1-" << regions.size() << "]: ";

    std::cin >> regionIdx;
  } while (regionIdx > regions.size());

  return Battle(&regions[regionIdx - 1]);
}

const Player& Game::GetCurrentPlayer() const {
  return m_Players[m_Turn];
}

size_t Game::FindWarInstigator() const {
  int min = m_Players[0].age;
  std::vector<int> potentialInstigators;
  for(size_t i = 0; i < m_Players.size() ; i++){
    if(m_Players[i].age < min){
      min = m_Players[i].age;
      potentialInstigators.clear();
    }

    if(m_Players[i].age == min){
      potentialInstigators.push_back(i);
    }
  }

  size_t randNum = rand() % potentialInstigators.size();
  return potentialInstigators[randNum];
}
