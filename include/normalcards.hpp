#pragma once
#include <cards.hpp>
class NormalCards: public Cards{
  public:
    NormalCards(std::string NameValue,int PowerValue) : Cards(NameValue),power(PowerValue){}
    int getPower() const{ return power;}
  private:
    int power{};
};
