#pragma once
#include <string>
class Cards{
  public:
    Cards(std::string NameValue) : name(NameValue){}
    virtual ~Cards(){} //polymorphic
    const std::string GetName() const{
      return name;
    }
  private:
  std::string name;
};
