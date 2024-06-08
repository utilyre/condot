#pragma once
#include <cards.hpp>
class NormalCards: public Cards{
  public:
    NormalCards(std::string NameValue,int PowerValue);
    int getPower() const;
  private:
    int power{};
};
