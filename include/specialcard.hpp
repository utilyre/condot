#pragma once

#include <card.hpp>

class SpecialCard : public Card {
  public:
    SpecialCard(std::string name);
    virtual ~SpecialCard() {}
    std::string GetName() const override;
  private:
    std::string m_Name;
};
