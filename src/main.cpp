#include <iostream>
#include <vector>

#include <game.hpp>
#include <player.hpp>

#define DEBUG

std::vector<Player> InputPlayers();

int main() {
#ifdef DEBUG
  std::vector<Player> players;
  players.emplace_back("John", "red", 17);
  players.emplace_back("Jane", "blue", 18);
  players.emplace_back("Rick", "yellow", 17);
#else
  auto players = InputPlayers();
#endif

  Game game(std::move(players));
  game.Start();
}

std::vector<Player> InputPlayers() {
  std::cout << "Welcome to Condottiere\n\n";

  int numPlayers;
  while (true) {
    std::cout << "How many players are you? ";
    std::cin >> numPlayers;
    if (numPlayers < 3) {
      std::cout << "Error: too few players (minimum is 3)\n\n";
      continue;
    }
    if (numPlayers > 6) {
      std::cout << "Error: too many players (maximum is 6)\n\n";
      continue;
    }

    break;
  }

  std::vector<Player> players;
  for (int i = 0; i < numPlayers; i++) {
    std::cout << "\nPlayer #" << i + 1 << ":\n";

    std::string name;
    std::cout << "Name: ";
    std::cin >> name;

    int age;
    std::cout << "Age: ";
    std::cin >> age;

    std::string color;
    std::cout << "Color: ";
    std::cin >> color;

    players.emplace_back(name, color, age);
  }

  return players;
}
