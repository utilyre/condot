#pragma once

#include <cstddef>
#include <vector>

#include <player.hpp>

class Turn {
public:
  explicit Turn(std::vector<Player>& players);

  size_t FindWarInstigator() const;
  const Player& GetCurrentPlayer() const;

private:
  size_t m_Current;
  std::vector<Player>& m_Players;
};
