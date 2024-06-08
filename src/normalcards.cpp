#include <cards.hpp>
#include <normalcards.hpp>

NormalCards::NormalCards(std::string NameValue,int PowerValue)
 : Cards(NameValue),power(PowerValue)
 {}
 
int NormalCards::getPower() const{
  return power;
}
