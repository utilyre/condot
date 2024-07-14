#include <cstddef>
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
  
  Vector2 BOTTOM{(GetScreenWidth() - float(570)) / 2  , GetScreenHeight() - float(200) };
  Vector2 LEFT  { 200  , (GetScreenHeight() - float(570)) / 2 };
  Vector2 TOP   {(GetScreenWidth() + float(570)) / 2 , 200};
  Vector2 RIGHT {GetScreenWidth() - float(200) , (GetScreenHeight() + float(570)) / 2 };

  switch (m_Position)
  {
  case Position::TOP:
    DrawRectangle((width - length) / 2, 0, length, thickness, RED);
    RenderRows ( assets , Vector2{TOP.x + 50, TOP.y + 50} , 180);
    RenderCards( assets , TOP ,180);
    break;
  case Position::RIGHT:
    DrawRectangle(width - thickness, (height - length) / 2, thickness, length, GREEN);
    RenderRows (assets,Vector2{ RIGHT.x - 50, RIGHT.y + 50}, 270);
    RenderCards(assets, RIGHT , 270);
    break;
  case Position::BOTTOM:
    DrawRectangle((width - length) / 2, height - thickness, length, thickness, BLUE);
    DrawText("pass", 420, 950, 30, BLACK);
    RenderRows (assets,Vector2{ BOTTOM.x - 50, BOTTOM.y - 50}, 0);
    RenderCards(assets, BOTTOM, 0);
    break;
  case Position::LEFT:
    DrawRectangle(0, (height - length) / 2, thickness, length, GRAY);
    RenderRows (assets,Vector2{ LEFT.x + 50, LEFT.y - 50}, 90);
    RenderCards(assets, LEFT, 90);
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

bool Player::PlayCard(){
  if (m_Position == Position::BOTTOM)
  {
    size_t index = 0;
    for(auto it = m_Cards.rbegin(); it != m_Cards.rend(); ++it)
    {
      Rectangle LowerLayer = {((GetScreenWidth() - float(570)) / 2) + (float) 50 * index , GetScreenHeight() - float(200) , 50  , 190};
      Rectangle UpperLayer = {((GetScreenWidth() - float(570)) / 2) + (float) 50 * index , GetScreenHeight() - float(200) , 120 , 190};
        
      if((CheckCollisionPointRec(GetMousePosition(), LowerLayer) ||
         (CheckCollisionPointRec(GetMousePosition(), UpperLayer) &&
         m_Cards.size() - 1 == index )) && 
          IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
          PickCard(index);
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

void Player::PickCard(const size_t& index){
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
            m_State->Set(State::BISHOP);
          }
          
          else if (card == Card::DRUMMER) {
            m_Cards.erase(m_Cards.begin() + index);
            if (!m_s.count("DRUMMER")) m_s.insert({"DRUMMER" , 1});
          }
          
          else if (card == Card::HEROINE) {
            m_Cards.erase(m_Cards.begin() + index);
            if (!m_s.count("HEROINE")) m_s["HEROINE"] = 1;
            else m_s["HEROINE"]++;
            std::cout << m_s["HEROINE"];
          }
          
          else if (card == Card::SCARECROW) {
            if(!m_Row.empty()) m_State->Set(State::SCARECROW);
            while(m_State->Get() == State::SCARECROW){
              size_t Idx{0};
              for(auto it = m_Row.rbegin(); it != m_Row.rend(); ++it)
              {
                Rectangle LowerLayer = {540 + (float) 50 * Idx , 830 , 50  , 50};
                Rectangle UpperLayer = {540 + (float) 50 * Idx , 830 , 120 , 50};
                BeginDrawing();
                EndDrawing();
                if((CheckCollisionPointRec(GetMousePosition(), LowerLayer) ||
                   (CheckCollisionPointRec(GetMousePosition(), UpperLayer) &&
                   m_Cards.size() - 1 == Idx )) && 
                  IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                  m_Row.erase(m_Row.begin() + Idx);
                  Add(Idx);
                  m_Cards.erase(m_Cards.begin() + index);
                  m_State->Set(State::ROTATING_TURN);
                }
                std::cout << Idx << " " << m_s["HEROINE"] << '\n';
                Idx++;
              }
            }
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

std::vector<Card>&  Player::GetCards(){
  return m_Cards;
}

void Player::Add(const size_t& index){
  size_t power = m_Row[index].GetPower();
  if (power == 1) {
    m_Cards.push_back(Card::MERCENARY_1);
  }

  else if (power == 2) {
    m_Cards.push_back(Card::MERCENARY_2);
  }

  else if (power == 3) {
    m_Cards.push_back(Card::MERCENARY_3);
  }
   
  else if (power == 4) {
    m_Cards.push_back(Card::MERCENARY_4);
  }
  
  else if (power == 5) {
    m_Cards.push_back(Card::MERCENARY_5);
  }
  
  else if (power == 6) {
    m_Cards.push_back(Card::MERCENARY_6);
  }
  
  else if (power == 10) {
    m_Cards.push_back(Card::MERCENARY_10);
 }
}
      
