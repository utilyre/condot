#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#define DEBUG

const std::string INDEX_TO_CITY[] = {
  /*  0: */ "bella",
  /*  1: */ "caline",
  /*  2: */ "enna",
  /*  3: */ "atela",
  /*  4: */ "pladaci",
  /*  5: */ "borge",
  /*  6: */ "dimase",
  /*  7: */ "rollo",
  /*  8: */ "mornia",
  /*  9: */ "olivadi",
  /* 10: */ "talmone",
  /* 11: */ "armento",
  /* 12: */ "lia",
  /* 13: */ "elinia",
};

const bool MAP[14][14] = {
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

struct Player {
  Player(std::string name, int age, std::string color)
      : name(name), age(age), color(color) {}

  std::string              name;
  int                      age;
  std::string              color;
  std::vector<std::string> cardsAvailable;
  std::vector<std::string> capturedCity;                      /*if the player wins the city add the city to the vector
                                                                and delete it from the playable cities.*/
  std::vector<std::string> cardsPlayed;
};

class Game{
public:
  Game(const std::vector<Player> players) : m_Players(players) {
    m_Turn = FindWarInstigator();
  }

  const Player& GetCurrentPlayer() const {
    return m_Players[m_Turn];
  }

private:
  size_t FindWarInstigator() const {
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

private:
  size_t m_Turn = 0;
  std::vector<Player> m_Players;
  std::string battleMarker; // TODO: set this field after determining the city
};

bool isCityValid(std::string choice){
  for(auto city : INDEX_TO_CITY) {
    if (choice == city) {
      return true;
    }
  }

  return false;
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

  /*
  NOTE: shuffle logic

  std::random_device rd;
  std::mt19937 g(rd());
  std::vector<std::string> cards{"1","1","1","1","1","1","1","1","1","1","2","2","2","2","2","2","2","2","3","3","3","3","3","3","3","3","4","4","4","4","4","4","4","4",
                                 "5","5","5","5","5","5","5","5","6","6","6","6","6","6","6","6","10","10","10","10","10","10","10","10","matarsak","matarsak","matarsak",
                                 "matarsak","matarsak","matarsak","matarsak","matarsak","matarsak","matarsak","matarsak","matarsak","matarsak","matarsak","matarsak","matarsak",
                                 "tablzan","tablzan","tablzan","tablzan","tablzan","tablzan","bahar","bahar","bahar","zemestan","zemestan","zemestan","shirdokht","shirdokht","shirdokht"};
 
   std::vector<std::string> playingCards{cards}; 
   shuffle(cards.begin(),cards.end(),g);
   
   for(int i{}; i < numPlayers;i++){
     for(int j{}; j < 10 ; j++){  
      players[i].cardsAvailable.push_back(cards.back());
      cards.pop_back();
     }
   }
  */

  Game game(players);

  std::string battleMarker;
  do {
    std::system("clear");

    std::cout << "Cities:\n";
    for (auto city : INDEX_TO_CITY) {
      std::cout << city << ' ';
    }

    std::cout << "\n\nChoose a city to start the war in.\n";
    std::cout << '@' << game.GetCurrentPlayer().name << ": ";
    std::cin >> battleMarker;
  } while (!isCityValid(battleMarker));

  std::system("clear");
  std::cout << "War position is at " << battleMarker << " city!";
}
