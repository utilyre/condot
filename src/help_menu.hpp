#pragma once

#include <asset_manager.hpp>
#include <entity.hpp>
#include <button.hpp>
#include <vector>
#include <card.hpp>

class HelpMenu : public Entity
{
  public:
    HelpMenu();
    void Render(const AssetManager&) const override;
    void Update() override;
    bool IsGettingDetail() const;
  private:
    Button m_BackButton;
    std::vector<Button> m_Buttons;
    bool m_ShowDetail;
    std::vector<bool> m_ShowDescription;
    std::vector<Card> m_Cards;
};
