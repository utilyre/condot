#include <game.hpp>
#include <player.hpp>

Game::Game(const std::vector<Player> players) : m_Players(players) {
  m_Turn = FindWarInstigator();
}

const Player& Game::GetCurrentPlayer() const {
  return m_Players[m_Turn];
}

void Game::setBattleMarker(std::string battleMarkerValue){
  battleMarker = battleMarkerValue;
}

const std::string Game::getBattleMarker() const{
  return battleMarker;
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
