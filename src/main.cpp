#include <iostream>
#include <string>
#include <vector>

#include <game.hpp>
#include <player.hpp>

#define DEBUG

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
    game.getCity().printCity();
    std::cout << "\n\nChoose a city to start the war in.\n";
    std::cout << '@' << game.GetCurrentPlayer().name << ": ";
    std::cin >> battleMarker;
  } while (!game.getCity().isCityValid(battleMarker));
  game.setBattleMarker(battleMarker);
  std::system("clear");
  std::cout << "War position is at " << game.getBattleMarker() << " city!";
}
