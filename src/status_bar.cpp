#include <algorithm>
#include <cstddef>
#include <raylib.h>

#include <asset_manager.hpp>
#include <player.hpp>
#include <status_bar.hpp>
#include <state.hpp>
#include <season.hpp>

StatusBar::StatusBar(State* state, Season* season) : 
 m_StatusButton("Status",Rectangle{ 10, 10, 120, 70}),
 m_State(state),
 m_Season(season)
 {}

void StatusBar::Render(const AssetManager& assets) const
{
  if (m_State->Get() != State::PLAYING_CARD &&
      m_State->Get() != State::SCARECROW)
  {
    return;
  }

  m_StatusButton.Render(assets);
  if (m_StatusButton.Hovered())
  {
    DrawRectangle(0, 0, 400, 400, WHITE);
    float VerticalSpacing = 10;
    for (auto& p : *m_Players)
    {
      float HorizotalSpacing = 40;
      DrawRectangle(10, VerticalSpacing, 20, 20, p.GetColor());
  
      DrawTextureEx(assets.Bishop,Vector2{HorizotalSpacing,VerticalSpacing}, 0, 0.2, WHITE);
      DrawText(TextFormat(" x %d", p.GetBishop()), 70, VerticalSpacing + 20, 10, BLACK);
      HorizotalSpacing += 60;
    
      DrawTextureEx(assets.Spy,Vector2{HorizotalSpacing,VerticalSpacing}, 0, 0.2, WHITE);
      DrawText(TextFormat(" x %d", p.GetSpy()), 130, VerticalSpacing + 20, 10, BLACK);
      HorizotalSpacing += 60;
    
      DrawTextureEx(assets.Heroine,Vector2{HorizotalSpacing,VerticalSpacing}, 0, 0.2, WHITE);
      DrawText(TextFormat(" x %d", p.GetHeroine()), 190, VerticalSpacing + 20, 10, BLACK);
      HorizotalSpacing += 60;
    
      DrawTextureEx(assets.Drummer,Vector2{HorizotalSpacing,VerticalSpacing}, 0, 0.2, WHITE);
      DrawText(TextFormat(" x %d", p.GetDrummer()), 250, VerticalSpacing + 20, 10, BLACK);

      DrawText(TextFormat("Score: %d",CalculateScore(p, GetBiggestNum())),290,VerticalSpacing + 20 , 20, BLACK);
      VerticalSpacing += assets.BackSide.height * 0.2;
    }
    DrawText("Season :",40, VerticalSpacing + 20 , 25 , BLACK);
    if (*m_Season == Season::WINTER)
    { 
      DrawText("winter", 150, VerticalSpacing + 20, 25, BLACK);
    }
    else if (*m_Season == Season::SPRING) 
    {
      DrawText("Spring", 150, VerticalSpacing + 20, 25, BLACK);
    }
    else if (*m_Season == Season::NONE) 
    {
      DrawText("None", 150, VerticalSpacing + 20, 25, BLACK);
    }
  }
}

void StatusBar::Update()
{
  auto State = m_State->Get();
  if (State != State::PLAYING_CARD &&
      State != State::SCARECROW)
  {
    return;
  }

  m_StatusButton.Update();
}

void StatusBar::Set(std::vector<Player>* players)
{
  m_Players = players;
}

int StatusBar::GetBiggestNum() const
{
  size_t BiggestNum = 0;
  size_t BishopNum = 0;
  std::vector<int> Cards;
  
  for (const auto& p : *m_Players) 
  {
    BishopNum += p.GetBishop();
    for (auto& c : p.GetRow()) 
    {
      int bn = c.GetPower();
      if(bn != 0 && std::count(Cards.begin(), Cards.end(), bn) == 0)
      {
        Cards.push_back(bn);
      }    
    }
      
  }
  if (!Cards.empty()) 
  {
    std::sort(Cards.begin(), Cards.end());
    BiggestNum = Cards[Cards.size() - BishopNum - 1];
  }
  return BiggestNum;
}

int StatusBar::CalculateScore(Player& p, int C) const
{
  int score{};
  int BNum{};

  for(const auto& c : p.GetRow())
  {
    int bn = c.GetPower();
    if (C == bn)
    {
      BNum++;
    }
    else if (bn > C) 
    {
      continue;
    }
    score += bn;
  }

  if (*m_Season == Season::WINTER)
  {
    score = p.GetRow().size();
  }

  if (p.GetDrummer() == true)
  {
    score *= 2;
  }

  if (*m_Season == Season::SPRING)
  {
     score += BNum * 3;
  }

  
  score += p.GetHeroine() * 10;
  score += p.GetSpy();
  
  return score;
  
}
