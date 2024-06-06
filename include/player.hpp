#pragma once

#include <string>
#include <vector>

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
