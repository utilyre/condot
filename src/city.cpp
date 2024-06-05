#include <iostream>
#include <city.hpp>
#include <string>

void City::printCity() const{
  std::cout << "Cities :\n";
  for(auto city : INDEX_TO_CITY){
    std::cout << city << ' ';
  }
}
  
bool City::isCityValid(std::string cityValue){
  for(auto city : INDEX_TO_CITY) {
    if (cityValue == city) {
      return true;
    }
  }

  return false;
}
