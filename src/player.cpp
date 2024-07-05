#include <memory>
#include <raylib.h>

#include <asset_manager.hpp>
#include <player.hpp>
#include <card.hpp>
#include <mercenary.hpp>
#include <bishop.hpp>
#include <drummer.hpp>

Player::Player(const std::string& name, Color color, Position position)
: m_Name(name),
  m_Color(color),
  m_Position(position)
{}

void Player::Update()
{
}

void Player::Render(const AssetManager& assets) const
{
  float width = GetScreenWidth();
  float height = GetScreenHeight();

  int length = 3 * height / 4;
  int thickness = 200;
  
  Vector2 bottom{(width - height) / 2 + 150, (height - assets.Drummer.height) / 2 + 470};
  Vector2 left{200, (height - length) / 2};
  Vector2 top{(width - length) / 2 + 140, 200};
  Vector2 right{width - thickness, (height - length) / 2 + 120};

  switch (m_Position)
  {
  case Position::TOP:
    DrawRectangle((width - length) / 2, 0, length, thickness, RED);
    RenderCards(assets, top ,180);
    break;
  case Position::RIGHT:
    DrawRectangle(width - thickness, (height - length) / 2, thickness, length, GREEN);
    RenderCards(assets, right, 270);
    break;
  case Position::BOTTOM:
    DrawRectangle((width - length) / 2, height - thickness, length, thickness, BLUE);
    RenderCards(assets, bottom, 0);
    break;
  case Position::LEFT:
    DrawRectangle(0, (height - length) / 2, thickness, length, GRAY);
    RenderCards(assets, left, 90);
    break;
  }
}

void Player::RenderCards(const AssetManager& assets, Vector2 cordinate, float rotation) const
{
  float ratio = 0.75;
  if (m_Position == Position::TOP || m_Position == Position::BOTTOM)
  {
    for (const auto& c : m_Cards)
    {
      DrawTextureEx(c->GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x += 50;
    }
  }

  if (m_Position == Position::LEFT || m_Position == Position::RIGHT)
  {
    for (const auto& c : m_Cards)
    {
      DrawTextureEx(c->GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.y += 50;
    }
  }
}

void Player::AddCard(std::unique_ptr<Card>&& card)
{
  m_Cards.push_back(std::move(card));
}
