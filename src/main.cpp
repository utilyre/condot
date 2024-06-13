#include <iostream>
#include <string>
#include <vector>

#include <card.hpp>
#include <normalcard.hpp>
#include <specialcard.hpp>
#include <game.hpp>
#include <player.hpp>

#define DEBUG

std::vector<Player> inputPlayers();

int main() {
  srand(time(0));

#ifdef DEBUG
  std::vector<Player> players{
    Player("John", "red", 17),
    Player("Jane", "blue", 18),
    Player("Rick", "yellow", 17),
  };
#else
  auto players = inputPlayers();
#endif
  std::string cardname{};
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
