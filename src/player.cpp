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
  if (m_State->Get() == State::PLAYING_CARD) {
    if(PlayCard()){
      m_State->Set(State::ROTATING_TURN);
    }
  }
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

bool Player::PlayCard(std::vector<Player>& player){
  if (m_Position == Position::BOTTOM)
  {
    size_t index = 0;
    for(auto it = m_Cards.rbegin(); it != m_Cards.rend(); ++it)
    {
      Rectangle LowerLayer = {590 + (float) 50 * index , 880 , 50  , 190};
      Rectangle UpperLayer = {590 + (float) 50 * index , 880 , 120 , 190};
        
      if((CheckCollisionPointRec(GetMousePosition(), LowerLayer) ||
         (CheckCollisionPointRec(GetMousePosition(), UpperLayer) &&
         m_Cards.size() - 1 == index )) && 
          IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
          PickCard(index,player);
          return true;
        }
      else if (CheckCollisionPointRec(GetMousePosition(),(Rectangle){420, 950, 70, 50}) &&
           IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
      {
        
      }
      index++;
    }
  }
    return false;
}
int Player::GetAge() const {
  return m_Age;
}

void Player::PickCard(const size_t& index , std::vector<Player>& player){
          auto card = m_Cards[index].GetType();
          if (card == Card::MERCENARY_1) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(1);
          }
          
          else if (card == Card::MERCENARY_2) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(2);
          }
          
          else if (card == Card::MERCENARY_3) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(3);
          }
          
          else if (card == Card::MERCENARY_4) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(4);
          }
          
          else if (card == Card::MERCENARY_5) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(5);
          }
          
          else if (card == Card::MERCENARY_6) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(6);
          }
          
          else if (card == Card::MERCENARY_10) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(10);
          }
          
          // TODO : does something with gameflow
          else if (card == Card::BISHOP) {
            m_Cards.erase(m_Cards.begin() + index);
            // TODO : Bishop();
          }
          
          else if (card == Card::DRUMMER) {
            m_Cards.erase(m_Cards.begin() + index);
            // TODO : bool drummer = true;
          }
          
          else if (card == Card::HEROINE) {
            m_Cards.erase(m_Cards.begin() + index);
            // TODO : int Heroine++;
          }
          
          else if (card == Card::SCARECROW) {
            m_Cards.erase(m_Cards.begin() + index);
            //TODO : Scarecrow();
          }
          
          else if (card == Card::SPRING) {
            m_Cards.erase(m_Cards.begin() + index);
            //TODO : Set(Season::SPRING);
          }
          
          else if (card == Card::SPY) {
            m_Cards.erase(m_Cards.begin() + index);
            //TODO : int Spy++;
            
          }
          
          else if (card == Card::TURNCOAT) {
            m_Cards.erase(m_Cards.begin() + index);
            // TODO : EndGame();
          }
          
          else if (card == Card::WINTER) {
            m_Cards.erase(m_Cards.begin() + index);
            // TODO : Set(Season::WINTER);
          }
          
}

void Player::SetPosition(const Position& position){
  m_Position = position;
}

void Player::Pass(){
  m_IsPassed = true;
}

bool Player::IsPassed(){
  return m_IsPassed;
}

const Position& Player::GetPosition() const{
  return m_Position;
}
