#pragma once

#include <card.hpp>

class NormalCard : public Card {
public:
  NormalCard(int power);

  std::string GetName() const;
  int GetPower() const;

private:
  int m_Power;
};
