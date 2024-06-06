#include <iostream>
#include <string>
#include <vector>

#include <game.hpp>
#include <player.hpp>

#define DEBUG

static Region g_Regions[14] = {
  Region("bella"),
  Region("caline"),
  Region("enna"),
  Region("atela"),
  Region("pladaci"),
  Region("borge"),
  Region("dimase"),
  Region("rollo"),
  Region("mornia"),
  Region("olivadi"),
  Region("talmone"),
  Region("armento"),
  Region("lia"),
  Region("elinia"),
};

static const bool MAP_ADJACENCY[14][14] = {
  /*                 0  1  2  3  4  5  6  7  8  9 10 11 12 13 */
  /*  0: bella   */ {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  /*  1: caline  */ {1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  /*  2: enna    */ {0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
  /*  3: altela  */ {0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
  /*  4: pladaci */ {1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0},
  /*  5: borge   */ {0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0},
  /*  6: dimase  */ {0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
  /*  7: rollo   */ {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
  /*  8: mornia  */ {0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0},
  /*  9: olivadi */ {0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0},
  /* 10: talmone */ {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
  /* 11: armento */ {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0},
  /* 12: lia     */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
  /* 13: elinia  */ {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
};

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

    players.emplace_back(name, age, color);
  }

  return players;
}

int main() {
  srand(time(0));

#ifdef DEBUG
  std::vector<Player> players{
    Player("John", 17, "red"),
    Player("Jane", 18, "blue"),
    Player("Rick", 17, "yellow"),
  };
#else
  auto players = inputPlayers();
#endif

  Map map(14, g_Regions, &MAP_ADJACENCY[0][0]);
  Game game(players, map);

  std::string battleMarker;
  do {
    std::system("clear");
    game.getCity().printCity();
    std::cout << "\n\nChoose a city to start the war in.\n";
    std::cout << '@' << game.GetCurrentPlayer().name << ": ";
    std::cin >> battleMarker;
  } while (!game.getCity().isCityValid(battleMarker));
  game.setBattleMarker(battleMarker);
  std::system("clear");
  std::cout << "War position is at " << game.getBattleMarker() << " city!";
}
