#include <cards.hpp>

Cards::Cards(std::string NameValue) : name(NameValue){}

const std::string Cards::GetName() const{
  return name;
}
