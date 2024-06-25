#pragma once

#include <specialcard.hpp>
#include <game.hpp>

class Matarsak : public SpecialCard{
  public:
    Matarsak(std::string name);
    void Ability() override;
  private:
};
