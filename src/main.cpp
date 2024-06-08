#include <iostream>
#include <string>
#include <vector>

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

  Game game(std::move(players));
  game.Start();
}

std::vector<Player> inputPlayers() {
  std::cout << "Welcome to Condottiere\n\n";

  int numPlayers;
  std::cout << "How many players are you? ";
  std::cin >> numPlayers;
  if (numPlayers < 3) {
    std::cout << "You need to be at least 3 to play this game\n";
    std::exit(EXIT_FAILURE);
  }
  if (numPlayers > 6) {
    std::cout << "You can be at most 6 to play this game\n";
    std::exit(EXIT_FAILURE);
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
