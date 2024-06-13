#include <iostream>
#include <vector>

#include <game.hpp>
#include <player.hpp>

#define DEBUG

std::vector<Player> inputPlayers();

int main() {
#ifdef DEBUG
  Player p1("John", "red", 17);
  Player p2("Jane", "blue", 18);
  Player p3("Rick", "yellow", 17);

  std::vector<Player> players;
  players.push_back(std::move(p1));
  players.push_back(std::move(p2));
  players.push_back(std::move(p3));
#else
  auto players = inputPlayers();
#endif

  Game game(std::move(players));
  game.Start();
}

std::vector<Player> inputPlayers() {
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
