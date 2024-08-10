#include <map>
#include<raylib.h>

#include <help_menu.hpp>
#include <asset_manager.hpp>
#include <button.hpp>
#include <card.hpp>

static const float BUTTON_WIDTH = 800;
static const float BUTTON_HEIGHT = 100;
static const float TEXT_HEIGHT = 800;
static const float TEXT_WIDTH = 1000;

static std::pmr::map<const char*, const char*> HelpDetail
{
  {"Bishop","Discard all copies of the highest value mercenary in play. \n\n\nPlace the favor marker in an empty region."},
  {"spy", "Add 1 to your strength. At the end of the battle, \n\n\nthe player with the most Spies takes the battle marker."},
  {"heroine", "Add 10 to your strength."},
  {"turncoat", "The battle ends immediately.\n\n\nThe battle winner will be determined as normal"},
  {"spring", "Add 3 to all copies of the highest value mercenary in play. \n\n\nThis card replaces the current season."},
  {"winter", "The value of each mercenary in play is 1.\n\n\nThis card replaces the current season."},
  {"scarecrow", "Take 1 mercenary from your row back to your hand.\n\n\nCan't take back special cards"},
  {"drummer", "Double the value of each mercenary in your row."},
};


HelpMenu::HelpMenu() :
  m_BackButton("Back", Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    GetScreenHeight() - 120.0f,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  }),    
  m_Buttons(
  {        
    Button("Bishop",Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    0,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  }),
    Button("Spy",Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    120,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  }),
    Button("Heroine",Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    240,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  }),
    Button("Turncoat",Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    360,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  }),
    Button("Spring",Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    480,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  }),
    Button("Winter",Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    600,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  }),
    Button("Scarecrow",Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    720,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  }),
    Button("Drummer",Rectangle{
    (GetScreenWidth() - BUTTON_WIDTH) / 2.0f,
    840,
    BUTTON_WIDTH,
    BUTTON_HEIGHT
  })
  }),
  m_ShowDetail(false)
{
  m_ShowDescription.insert(m_ShowDescription.end(),8,false);
  m_Cards.push_back(Card::BISHOP);
  m_Cards.push_back(Card::SPY);
  m_Cards.push_back(Card::HEROINE);
  m_Cards.push_back(Card::TURNCOAT);
  m_Cards.push_back(Card::SPRING);
  m_Cards.push_back(Card::WINTER);
  m_Cards.push_back(Card::SCARECROW);
  m_Cards.push_back(Card::DRUMMER);
  
}

void HelpMenu::Render(const AssetManager& assets) const
{
  
  if (!m_ShowDetail)
  {
    for (const auto& b : m_Buttons) 
    {
      b.Render(assets); 
    }
  }
  else 
  {
    m_BackButton.Render(assets);
  }
  
  
  size_t index = 0;
  for (auto& [key, value] : HelpDetail)
  {
    if (m_ShowDescription[index]) 
    {
      DrawRectangle(
        (GetScreenWidth() - TEXT_WIDTH) / 2.0f,
        (GetScreenHeight() - TEXT_HEIGHT) / 2.0f,
        TEXT_WIDTH,
        TEXT_HEIGHT,
        WHITE
      );
      
      DrawTextEx(
        assets.PrimaryFont,
        key,
        Vector2{GetScreenWidth() / 2.0f - 50, (GetScreenHeight() - TEXT_HEIGHT) / 2.0f},
        70,
         5,
        BLACK
      );
      
      DrawTextEx(
        assets.PrimaryFont,
        value,
        Vector2{(GetScreenWidth() - TEXT_WIDTH) / 2.0f + 50, (GetScreenHeight() - TEXT_HEIGHT) / 2.0f + 80},
        45,
        3,
        BLACK
      );

      DrawTextureEx(
        m_Cards[index].GetAsset(assets),
        Vector2{(GetScreenWidth() - m_Cards[index].GetAsset(assets).width) / 2.0f, GetScreenHeight() / 2.0f},
        0,
        1,
        WHITE
      );
    }
    index++;     
  }  
}

void HelpMenu::Update()
{
  if (!m_ShowDetail)
  {
    for (auto& b : m_Buttons)
    {
      b.Update();
    }
  }

  for (size_t index = 0; index < m_Buttons.size(); ++index) 
  {
    if (m_Buttons[index].Pressed())
    {
       m_ShowDetail = true;
       m_ShowDescription[index] = true;  
    }
  }

  if(m_ShowDetail)
  {
    m_BackButton.Update(); 
  }

  if (m_BackButton.Pressed()) 
  {
    m_ShowDetail = false;
    m_ShowDescription.clear();
    m_ShowDescription.insert(m_ShowDescription.end(), 8, false);
  }
}

bool HelpMenu::IsGettingDetail() const
{
  return m_ShowDetail;
}
