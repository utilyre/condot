#include <raylib.h>

#include <asset_manager.hpp>
#include <player.hpp>
#include <span>
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
      m_State->Get() != State::StatusBar &&
      m_State->Get() != State::SCARECROW)
  {
    return;
  }
  m_StatusButton.Render(assets);
  if (m_State->Get() == State::StatusBar)
  {
    DrawRectangle(0, 0, 400, 400, WHITE);
    float VerticalSpacing = 10;
    int BiggestNum = GetScore();
    for (auto* p : *m_Players)
    {
      float HorizotalSpacing = 40;
      DrawRectangle(10, VerticalSpacing, 20, 20, p->GetColor());
  
      DrawTextureEx(assets.Bishop,Vector2{HorizotalSpacing,VerticalSpacing}, 0, 0.2, WHITE);
      DrawText(TextFormat(" x %d", p->GetBishop()), 70, VerticalSpacing + 20, 10, BLACK);
      HorizotalSpacing += 60;
    
      DrawTextureEx(assets.Spy,Vector2{HorizotalSpacing,VerticalSpacing}, 0, 0.2, WHITE);
      DrawText(TextFormat(" x %d", p->GetSpy()), 130, VerticalSpacing + 20, 10, BLACK);
      HorizotalSpacing += 60;
    
      DrawTextureEx(assets.Heroine,Vector2{HorizotalSpacing,VerticalSpacing}, 0, 0.2, WHITE);
      DrawText(TextFormat(" x %d", p->GetHeroine()), 190, VerticalSpacing + 20, 10, BLACK);
      HorizotalSpacing += 60;
    
      DrawTextureEx(assets.Drummer,Vector2{HorizotalSpacing,VerticalSpacing}, 0, 0.2, WHITE);
      DrawText(TextFormat(" x %d", p->GetDrummer()), 250, VerticalSpacing + 20, 10, BLACK);
      DrawText(TextFormat("Score:%d",p->CalculateScore(BiggestNum)), 290, VerticalSpacing + 20, 20, BLACK);
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
      State != State::StatusBar &&
      State != State::SCARECROW)
  {
    return;
  }
  m_StatusButton.Update();
  
  if (m_StatusButton.Hovered())
  {
    m_State->Set(State::StatusBar);
  }
  
  else if (m_State->GetPrev() == State::PLAYING_CARD) 
  {
    m_State->Set(State::PLAYING_CARD);
  }

  else if (m_State->GetPrev() == State::SCARECROW)
  {
    m_State->Set(State::SCARECROW);
  }
}

void StatusBar::Set(std::vector<Player*>* players)
{
  m_Players = players;
}

int StatusBar::GetScore() const
{
  int BishopNum = 0;
  int BiggestNum = 0;

  for (auto& p : *m_Players)
  {
    if (p->GetBishop() == 1) 
    {
      BishopNum++;
      p->DecreaseBishop();
      break;
    }
  }

  for (int counter = 0; counter < BishopNum; ++counter)
  {
    for (const auto& p : *m_Players)
    {
      if (BiggestNum < p->GetBiggestNum())
      {
        BiggestNum = p->GetBiggestNum();
      }
    }

    for (auto& p : *m_Players)
    {
      p->DeleteCard(BiggestNum);
    }
    BiggestNum = 0;
  }

  for (const auto& p : *m_Players)
  {
    if (BiggestNum < p->GetBiggestNum()){
      BiggestNum = p->GetBiggestNum();
    }
  }
  
  for (const auto& p : *m_Players) 
  {
    if(p->GetHeroine() > 0)
    {
      BiggestNum = 10;
    }
  }

  return BiggestNum;
}
