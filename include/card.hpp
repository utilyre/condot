#pragma once

#include <string>

class Card {
public:
  virtual ~Card() {}
  virtual std::string GetName() const = 0;
};
