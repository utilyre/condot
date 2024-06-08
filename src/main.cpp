#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include<cards.hpp>
#include<normalcards.hpp>
#include<specialcards.hpp>
#include <game.hpp>
#include <player.hpp>

#define DEBUG

std::vector<Player> inputPlayers();

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

  Game game(std::move(players));
  //game.Start();
  for(auto& card : game.GetCards()){
   if(auto* ptr = dynamic_cast<NormalCards*>(card.get())){
    std:: cout << ptr->GetName()<< " -> " << ptr->getPower() << '\n';
   }
  }
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
