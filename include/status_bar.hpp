#pragma once

#include <vector>

#include <entity.hpp>
#include <player.hpp>
#include <asset_manager.hpp>
#include <season.hpp>

class StatusBar : public Entity
{
  public:
    StatusBar();
    StatusBar(State*, Season*);
    void Update() override;
    void Render(const AssetManager&) const override;
    void Set(std::vector<Player>*);
    int GetBiggestNum() const;
    int CalculateScore(Player&, int) const;
  private:
    std::vector<Player>* m_Players;
    Button m_StatusButton;
    State* m_State;
    Season* m_Season;
    
};
