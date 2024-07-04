#include "raylib.h"
#include "specialcard.hpp"
#include <asset_manager.hpp>
#include <player.hpp>

Player::Player(const std::string& name, Color color, Position position)
: m_Name(name),
  m_Color(color),
  m_Position(position),
  m_Cards({
            Card("drummer"),
            Card("drummer"),
            Card("drummer"),
            Card("drummer"),
            Card("drummer"),
            Card("drummer"),
            Card("drummer"),
            Card("drummer"),
            Card("bishop"),
            
          })
{}

void Player::Update()
{
}

void Player::Render(const AssetManager& assets) const
{
  int monitor = GetCurrentMonitor();
  float width = GetMonitorWidth(monitor);
  float height = GetMonitorHeight(monitor);

  int length = 3 * height / 4;
  int thickness = 200;
  float ratio = 0.75;
  Vector2 bottom{(width - height) / 2 + 150, (height - assets.Drummer.height) / 2 + 470};
  
  switch (m_Position)
  {
  case Position::TOP:
    DrawRectangle((width - length) / 2, 0, length, thickness, RED);
    break;
  case Position::RIGHT:
    DrawRectangle(width - thickness, (height - length) / 2, thickness, length, GREEN);
    break;
  case Position::BOTTOM:
    DrawRectangle((width - length) / 2, height - thickness, length, thickness, BLUE);
    break;
  case Position::LEFT:
    DrawRectangle(0, (height - length) / 2, thickness, length, GRAY);
    break;
  }
  for(const auto& c : m_Cards){
    if(c.m_Name == "drummer"){
        DrawTextureEx(assets.Drummer, bottom , 0.0 , ratio , WHITE);
        bottom.x += 50;
    }
    else if(c.m_Name == "bishop"){
        DrawTextureEx(assets.Bishop, Vector2(bottom.x , bottom.y) , 0.0 , ratio , WHITE);
        bottom.x += 50;
    }
  }
}
