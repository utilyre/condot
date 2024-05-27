#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

struct Player {
  Player(std::string name, int age, std::string color)
      : name(name), age(age), color(color) {}

  std::string name;
  int age;
  std::string color;
};

int main() {
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

    players.emplace_back(name, age, color);
  }
  std::vector<std::string> cards{"1","1","1","1","1","1","1","1","1","1","2","2","2","2","2","2","2","2","3","3","3","3","3","3","3","3","4","4","4","4","4","4","4","4",
                                 "5","5","5","5","5","5","5","5","6","6","6","6","6","6","6","6","10","10","10","10","10","10","10","10","matarsak","matarsak","matarsak",
                                 "matarsak","matarsak","matarsak","matarsak","matarsak","matarsak","matarsak","matarsak","matarsak","matarsak","matarsak","matarsak","matarsak",
                                 "tablzan","tablzan","tablzan","tablzan","tablzan","tablzan","bahar","bahar","bahar","zemestan","zemestan","zemestan","shirdokht","shirdokht","shirdokht"};
  for (auto p : players) {
    std::cout << "-----------------\n";
    std::cout << p.name << " in the age of " << p.age << " has color " << p.color
              << '\n';
  }
}
