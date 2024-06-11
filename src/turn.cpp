#include <climits>

#include <turn.hpp>

Turn::Turn(std::vector<Player>& players)
: m_Players(players)
{
  m_Current = FindWarInstigator();
}

size_t Turn::FindWarInstigator() const {
  int min = INT_MAX;
  std::vector<size_t> potentialInstigators;
  for (size_t i = 0; i < m_Players.size() ; i++) {
    if (m_Players[i].GetAge() < min) {
      min = m_Players[i].GetAge();
      potentialInstigators.clear();
    }

    if (m_Players[i].GetAge() == min) {
      potentialInstigators.push_back(i);
    }
  }

  size_t randNum = rand() % potentialInstigators.size();
  return potentialInstigators[randNum];
}

const Player& Turn::GetCurrentPlayer() const {
  return m_Players[m_Current];
}
