#pragma once
#include <string>
class Cards{
  public:
    Cards(std::string name);
    const std::string GetName() const;
    virtual ~Cards(){} //polymorphic
  private:
  std::string name;
};
