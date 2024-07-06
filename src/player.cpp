#include <memory>
#include <raylib.h>

#include <asset_manager.hpp>
#include <player.hpp>
#include <card.hpp>
#include <mercenary.hpp>
#include <bishop.hpp>
#include <drummer.hpp>

Player::Player(const std::string& name, Color color,size_t age, Position position)
: m_Name(name),
  m_Color(color),
  m_Position(position),
  m_Age(age)
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

const size_t& Player::GetAge() const {
  return m_Age;
}

const std::string Player::GetName() const{
  return m_Name;
}

std::unique_ptr<Card> Player::TakeCard(size_t& pos)
{
  std::unique_ptr<Card>& card = *(m_Cards.begin() + pos);
  std::unique_ptr<Card> c =  std::move(card);
  m_Cards.erase(m_Cards.begin() + pos);
  return c;
  
}

const std::vector<std::unique_ptr<Card>>& Player::GetCards() const{
  return m_Cards;
} 

bool Player::IsCollided(AssetManager& assets){
    size_t i = 0;
    for(auto it = m_Cards.rbegin(); it != m_Cards.rend(); ++it){
      Rectangle LowerLayer = {570 + (float) 50 * i,880, 50 ,(float) (*it)->GetAsset(assets).height};
      if(CheckCollisionPointRec(GetMousePosition(), LowerLayer) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
        std::unique_ptr<Card> card = TakeCard(i);
        return true;
      }
      i++;
    }
    return false;
}
