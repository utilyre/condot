#include <cmath>
#include <raylib.h>

#include <asset_manager.hpp>
#include <state.hpp>
#include <player.hpp>
#include <card.hpp>
#include <mercenary.hpp>

Player::Player(State* state, const std::string& name, Color color, int age, Position position)
: m_State(state),
  m_Name(name),
  m_Color(color),
  m_Age(age),
  m_Position(position),
  m_IsPassed(false)
{
}

void Player::Update()
{
    PlayCard();
   // m_State->Set(State::ROTATING_TURN);
}

void Player::AddCard(Card card)
{
  m_Cards.push_back(card);
}

void Player::Render(const AssetManager& assets) const
{
  float width = GetScreenWidth();
  float height = GetScreenHeight();

  int length = 3 * height / 4;
  int thickness = 200;
  
  Vector2 bottom{590  , 880};
  Vector2 left  {200  , 175};
  Vector2 top   {1160 , 200};
  Vector2 right {1720 , 750};

  switch (m_Position)
  {
  case Position::TOP:
    DrawRectangle((width - length) / 2, 0, length, thickness, RED);
    RenderRows( assets , Vector2{1210 , 250} , 180);
    RenderCards( assets , top ,180);
    break;
  case Position::RIGHT:
    DrawRectangle(width - thickness, (height - length) / 2, thickness, length, GREEN);
    RenderRows(assets,Vector2{ 1670 , 800}, 270);
    RenderCards(assets, right, 270);
    break;
  case Position::BOTTOM:
    DrawRectangle((width - length) / 2, height - thickness, length, thickness, BLUE);
    DrawText("pass", 420, 950, 30, BLACK);
    RenderRows(assets,Vector2{540 , 830}, 0);
    RenderCards(assets, bottom, 0);
    break;
  case Position::LEFT:
    DrawRectangle(0, (height - length) / 2, thickness, length, GRAY);
    RenderRows(assets,Vector2{250 , 125}, 90);
    RenderCards(assets, left, 90);
    break;
  }
}

void Player::RenderRows(const AssetManager& assets, Vector2 cordinate, float rotation) const
{
  float ratio = 0.75;
  if (m_Position == Position::TOP)
  {
    for (auto c = m_Row.rbegin(); c != m_Row.rend(); ++c)
    {
      DrawTextureEx(c->GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x -= 50;
    }
  }

  if (m_Position == Position::BOTTOM)
  {
    for (const auto& c : m_Row)
    {
      DrawTextureEx(c.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x += 50;
    }
    
  }
  if (m_Position == Position::LEFT)
  {
    for (const auto& c : m_Row)
    {
      DrawTextureEx(c.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.y += 50;
    }
  }

  if (m_Position == Position::RIGHT)
  {
    for(auto c = m_Row.rbegin(); c != m_Row.rend(); ++c)
    {
      DrawTextureEx(c->GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.y -= 50;
      
    }  
  }
}

void Player::RenderCards(const AssetManager& assets, Vector2 cordinate, float rotation) const
{
  float ratio = 0.75;
  if (m_Position == Position::TOP)
  {
    for (auto c = m_Cards.rbegin(); c != m_Cards.rend(); ++c)
    {
      DrawTextureEx(c->GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x -= 50;
    }
  }

  if (m_Position == Position::BOTTOM)
  {
    for (const auto& c : m_Cards)
    {
      DrawTextureEx(c.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x += 50;
    }
    
  }
  
  if (m_Position == Position::LEFT)
  {
    for (const auto& c : m_Cards)
    {
      DrawTextureEx(c.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.y += 50;
    }
  }
  
  if (m_Position == Position::RIGHT)
  {
    for(auto c = m_Cards.rbegin(); c != m_Cards.rend(); ++c)
    {
      DrawTextureEx(c->GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.y -= 50;
      
    }  
  }
}

void Player::PlayCard(){
  if (m_Position == Position::BOTTOM)
  {
    size_t index = 0;
    for(auto it = m_Cards.rbegin(); it != m_Cards.rend(); ++it)
    {
      Rectangle LowerLayer = {570 + (float) 50 * index , 880 , 50  , 190};
    //Rectangle UpperLayer = {570 + (float) 50 * index , 880 , 120 , 190};
        
      if((CheckCollisionPointRec(GetMousePosition(), LowerLayer) &&
         //(CheckCollisionPointRec(GetMousePosition(), UpperLayer) &&
         // m_Cards.size() - 1 == i )) && 
          IsMouseButtonPressed(MOUSE_LEFT_BUTTON)))
        {
          auto card = PickCard(index);
          AddRowCard(card);
        }
      else if (CheckCollisionPointRec(GetMousePosition(),(Rectangle){420, 950, 70, 50}) &&
           IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){}
      index++;
    }
  }
    
}
int Player::GetAge() const {
  return m_Age;
}

const Card& Player::PickCard(const size_t& position){
  Card& card = *(m_Cards.begin() + position);
  m_Cards.erase(m_Cards.begin() + position);
  return card;
}

void Player::SetPosition(const Position& position){
  m_Position = position;
}

void Player::Pass(){
  m_IsPassed = true;
}

void Player::AddRowCard(const Card& card){
  m_Row.push_back(card);
}

bool Player::IsPassed(){
  return m_IsPassed;
}

const Position& Player::GetPosition() const{
  return m_Position;
}
