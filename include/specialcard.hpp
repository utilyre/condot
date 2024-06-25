#pragma once

#include <card.hpp>

class SpecialCard : public Card {
  public:
    SpecialCard(std::string name);
    virtual ~SpecialCard() {}
    std::string GetName() const override;
    virtual void Ability() = 0;
  private:
    std::string m_Name;
};
