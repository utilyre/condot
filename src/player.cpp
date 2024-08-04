#include <raylib.h>

#include <asset_manager.hpp>
#include <state.hpp>
#include <event.hpp>
#include <player.hpp>
#include <card.hpp>
#include <mercenary.hpp>
#include <button.hpp>

static const int CARD_WIDTH = 164;
static const int CARD_HEIGHT = 255;
static const float CARD_SCALE = 0.15f;

Player::Player(
  State* state,
  Event* rotateTurnEvent,
  Event* restartbattle,
  const std::string& name,
  Color color,
  int age,
  Position position
)
: m_State(state),
  m_RotateTurnEvent(rotateTurnEvent),
  m_RestartBattle(restartbattle),
  m_Name(name),
  m_Color(color),
  m_Age(age),
  m_Position(position),
  m_IsPassed(false),
  m_Spy(0),
  m_Heroine(0),
  m_Drummer(false),
  m_Bishop(0),
  m_PassButton ("SURRENDER",Rectangle(0,GetScreenHeight() - 100 , 170 , 100))
{
}

void Player::Update()
{
  auto state = m_State->Get();

  if (state != State::PLAYING_CARD &&
      state != State::SCARECROW){
    return;
  }
    bool RotateStatus = false;
    m_PassButton.Update();  
    if(state == State::PLAYING_CARD)
      RotateStatus = PlayCard();
    
    else if (m_State->Get() == State::SCARECROW)
      RotateStatus = RetrieveCard();
    
    //else if (m_State->Get() == BISHOP)
    if(RotateStatus == true && m_State->Get() == State::PLAYING_CARD)
    {
      bool PassStatus = false;
      bool PlayStatus = true;
      if(IsPassed())
      {
        m_IsPassed = PassStatus;
        m_RotateTurnEvent->Raise(this, &PassStatus);
        m_IsPassed = PassStatus;
      }
      else
      {
        m_RotateTurnEvent->Raise(this, &PlayStatus);
      }
    }
}

void Player::AddCard(Card card)
{
  m_Cards.push_back(card);
}

void Player::Render(const AssetManager& assets) const
{
  auto state = m_State->Get();
  if (state != State::PLAYING_CARD &&
      state != State::SCARECROW){
    return;
  }
  
 const float SCREEN_WIDTH  = GetScreenWidth();
 const float SCREEN_HEIGHT = GetScreenHeight();

 const float SCALE = CARD_SCALE * SCREEN_HEIGHT * SCREEN_WIDTH / (CARD_HEIGHT * CARD_WIDTH * 12);
 const float THICKNESS = SCALE  * (CARD_HEIGHT + 50);
 const float HORIZONTAL_SPACING = SCALE * (9.0 * CARD_WIDTH / 2 + CARD_WIDTH); 

 const Vector2 SCREEN_BOTTOM_LEFT  {SCALE * (CARD_HEIGHT * 2 + 50) , SCREEN_HEIGHT - SCALE * (CARD_HEIGHT + 50)};
 const Vector2 SCREEN_BOTTOM_RIGHT {SCREEN_WIDTH - SCALE * (CARD_HEIGHT * 2 + 50) - HORIZONTAL_SPACING, SCREEN_HEIGHT - SCALE * (CARD_HEIGHT + 50)};
 
 const Vector2 SCREEN_TOP_LEFT  {SCALE * (CARD_HEIGHT * 2 + 50) + HORIZONTAL_SPACING, SCALE * (CARD_HEIGHT + 50)};
 const Vector2 SCREEN_TOP_RIGHT {SCREEN_WIDTH - SCALE * (CARD_HEIGHT * 2 + 50) , SCALE * (CARD_HEIGHT + 50)};
 
 const Vector2 SCREEN_LEFT   {SCALE * (CARD_HEIGHT + 50), (SCREEN_HEIGHT - HORIZONTAL_SPACING) / 2};
 const Vector2 SCREEN_RIGHT  {SCREEN_WIDTH - SCALE * (CARD_HEIGHT + 50) , (SCREEN_HEIGHT + HORIZONTAL_SPACING) / 2};
   
  switch (m_Position)
  {
  case Position::TOP_LEFT:
    DrawRectangle(SCALE * (CARD_HEIGHT * 2 + 50) , 0 , HORIZONTAL_SPACING , THICKNESS , GetColor());
    RenderRows ( assets , Vector2{SCREEN_TOP_LEFT.x , SCREEN_TOP_LEFT.y + CARD_HEIGHT * SCALE / 2} , 180, SCALE);
    RenderCards( assets , SCREEN_TOP_LEFT ,180, SCALE);
    break;
    
  case Position::TOP_RIGHT:
    DrawRectangle(SCREEN_WIDTH - SCALE * (CARD_HEIGHT * 2 + 50) - HORIZONTAL_SPACING, 0 , HORIZONTAL_SPACING , THICKNESS , GetColor());
    RenderRows(assets,Vector2{SCREEN_TOP_RIGHT.x , SCREEN_TOP_RIGHT.y + CARD_HEIGHT * SCALE / 2} , 180, SCALE);
    RenderCards(assets, SCREEN_TOP_RIGHT, 180, SCALE);
    break;
    
  case Position::BOTTOM_LEFT:
    DrawRectangle(SCALE * (CARD_HEIGHT * 2 + 50) , SCREEN_HEIGHT - THICKNESS , HORIZONTAL_SPACING , THICKNESS , GetColor());
    RenderRows (assets , Vector2{ SCREEN_BOTTOM_LEFT.x , SCREEN_BOTTOM_LEFT.y - CARD_HEIGHT * SCALE / 2} , 0, SCALE);
    m_PassButton.Render(assets);
    RenderCards(assets , SCREEN_BOTTOM_LEFT , 0, SCALE);
    break;
    
  case Position::BOTTOM_RIGHT:
    DrawRectangle(SCREEN_WIDTH - SCALE * (CARD_HEIGHT * 2 + 50) - HORIZONTAL_SPACING , SCREEN_HEIGHT - THICKNESS , HORIZONTAL_SPACING , THICKNESS , GetColor());
    RenderRows (assets , Vector2{ SCREEN_BOTTOM_RIGHT.x , SCREEN_BOTTOM_RIGHT.y - CARD_HEIGHT * SCALE / 2} , 0,SCALE);
    RenderCards(assets , SCREEN_BOTTOM_RIGHT , 0, SCALE);
    break;
    
  case Position::RIGHT:
    DrawRectangle(SCREEN_WIDTH - THICKNESS, (SCREEN_HEIGHT - HORIZONTAL_SPACING) / 2, HORIZONTAL_SPACING , HORIZONTAL_SPACING , GetColor());
    RenderRows (assets , Vector2{ SCREEN_RIGHT.x - CARD_HEIGHT * SCALE / 2, SCREEN_RIGHT.y} , 270, SCALE);
    RenderCards(assets , SCREEN_RIGHT , 270, SCALE);
    break;
    
  case Position::LEFT:
    DrawRectangle(0, (SCREEN_HEIGHT - HORIZONTAL_SPACING) / 2, THICKNESS  , HORIZONTAL_SPACING , m_Color);
    RenderRows (assets , Vector2{ SCREEN_LEFT.x + CARD_HEIGHT * SCALE / 2 , SCREEN_LEFT.y} , 90, SCALE);
    RenderCards(assets , SCREEN_LEFT, 90, SCALE);
    break;
  }
}

void Player::RenderRows(const AssetManager& assets, Vector2 cordinate, float rotation, float ratio) const
{
 const float SCALE = CARD_SCALE * GetScreenHeight() * GetScreenWidth() / (CARD_HEIGHT * CARD_WIDTH * 12);
  if (m_Position == Position::TOP_LEFT)
  {
    for (auto c = m_Row.rbegin(); c != m_Row.rend(); ++c)
    {
      DrawTextureEx(c->GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x -= CARD_WIDTH / 2.0 * SCALE;
    }
  }
  
  if (m_Position == Position::TOP_RIGHT)
  {
    for (auto c = m_Row.rbegin(); c != m_Row.rend(); ++c)
    {
      DrawTextureEx(c->GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x -= CARD_WIDTH / 2.0 * SCALE;
    }
  }
  
  if (m_Position == Position::BOTTOM_LEFT)
  {
    for(const auto& c : m_Row)
    {
      DrawTextureEx(c.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x += CARD_WIDTH / 2.0 * SCALE;
    }
  }

  if (m_Position == Position::BOTTOM_RIGHT)
  {
    for (const auto& c : m_Row)
    {
      DrawTextureEx(c.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x += CARD_WIDTH / 2.0 * SCALE;
    }
    
  }
  
  if (m_Position == Position::LEFT)
  {
    for (const auto& c : m_Row)
    {
      DrawTextureEx(c.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.y += CARD_WIDTH / 2.0 * SCALE;
    }
  }

  if (m_Position == Position::RIGHT)
  {
    for(auto c = m_Row.rbegin(); c != m_Row.rend(); ++c)
    {
      DrawTextureEx(c->GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.y -= CARD_WIDTH / 2.0 * SCALE;
      
    }  
  }
}

void Player::RenderCards(const AssetManager& assets, Vector2 cordinate, float rotation, float ratio) const
{
   
  const float SCALE = CARD_SCALE * GetScreenHeight() * GetScreenWidth() / (CARD_HEIGHT * CARD_WIDTH * 12);
  Card card = Card::BACKSIDE;
  if (m_Position == Position::TOP_LEFT)
  {
    for (size_t c{} ; c < m_Cards.size() ; ++c)
    {
      DrawTextureEx(card.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x -= CARD_WIDTH / 2.0 * SCALE;
    }
  }

  if (m_Position == Position::TOP_RIGHT)
  {
    for (size_t c{} ; c < m_Cards.size() ; ++c)
    {
      DrawTextureEx(card.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x -= CARD_WIDTH / 2.0 * SCALE;
    }
  }
  
  if (m_Position == Position::BOTTOM_LEFT)
  {
    for (const auto& c : m_Cards)
    {
      DrawTextureEx(c.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x += CARD_WIDTH / 2.0 * SCALE;
    }
    
  }
  
  if (m_Position == Position::BOTTOM_RIGHT)
  {
    for (size_t c{}; c < m_Cards.size(); ++c)
    {
      DrawTextureEx(card.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x += CARD_WIDTH / 2.0 * SCALE;
    }
    
  }
  if (m_Position == Position::LEFT)
  {
    for (size_t c{} ; c < m_Cards.size(); ++c)
    {
      DrawTextureEx(card.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.y += CARD_WIDTH / 2.0 * SCALE;
    }
  }
  
  if (m_Position == Position::RIGHT)
  {
    for(size_t c{} ; c < m_Cards.size() ; ++c)
    {
      DrawTextureEx(card.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.y -= CARD_WIDTH / 2.0 * SCALE;
      
    }  
  }
}

bool Player::PlayCard(){

  const float scale = CARD_SCALE * GetScreenWidth() * GetScreenHeight() / (CARD_HEIGHT * CARD_WIDTH * 12);
  
  if (m_Position == Position::BOTTOM_LEFT)
  {
    size_t index = 0;
    for(auto it = m_Cards.rbegin(); it != m_Cards.rend(); ++it)
    {
      Rectangle LowerLayer = {scale * (CARD_HEIGHT * 2 + 50) + CARD_WIDTH / 2.0f * scale * index , GetScreenHeight() - scale * (CARD_HEIGHT + 50), CARD_WIDTH / 2.0f * scale , CARD_HEIGHT * scale};
      Rectangle UpperLayer = {scale * (CARD_HEIGHT * 2 + 50) + CARD_WIDTH / 2.0f * scale * index , GetScreenHeight() - scale * (CARD_HEIGHT + 50), CARD_WIDTH * scale , CARD_HEIGHT * scale};
        
      if((CheckCollisionPointRec(GetMousePosition(), LowerLayer) ||
         (CheckCollisionPointRec(GetMousePosition(), UpperLayer) &&
         m_Cards.size() - 1 == index )) && 
          IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
      {
        bool status = PickCard(index);
        return status;
      }
        
      else if (m_PassButton.Pressed())
      {
        m_IsPassed = true;  
        return true;
      }
      index++;
    }
  }
    return false;
}
int Player::GetAge() const {
  return m_Age;
}

bool Player::PickCard(const size_t& index){
          auto card = m_Cards[index].GetType();
          if (card == Card::MERCENARY_1) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(1);
            return true;
          }
          
          else if (card == Card::MERCENARY_2) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(2);
            return true;
          }
          
          else if (card == Card::MERCENARY_3) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(3);
            return true;
          }
          
          else if (card == Card::MERCENARY_4) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(4);
            return true;
          }
          
          else if (card == Card::MERCENARY_5) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(5);
            return true;
          }
          
          else if (card == Card::MERCENARY_6) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(6);
            return true;
          }
          
          else if (card == Card::MERCENARY_10) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Row.emplace_back(10);
            return true;
          }
          
          // TODO : does something with gameflow
          else if (card == Card::BISHOP) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Bishop++;
            return true;
          }
          
          else if (card == Card::DRUMMER) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Drummer = true;
            return true;
          }
          
          else if (card == Card::HEROINE) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Heroine++;
            return true;
          }
          
          else if (card == Card::SCARECROW) {
            if(m_Row.empty()) return false;
            m_Cards.erase((m_Cards.begin() + index));
            m_State->Set(State::SCARECROW);
            return true; 
          }
          
          else if (card == Card::SPRING) {
            m_Cards.erase(m_Cards.begin() + index);
            m_State->Set(State::SPRING);
            return true;
          }
          
          else if (card == Card::SPY) {
            m_Cards.erase(m_Cards.begin() + index);
            m_Spy++;
            return true;
          }
          
          else if (card == Card::TURNCOAT) {
            m_Cards.erase(m_Cards.begin() + index);
            m_RestartBattle->Raise(this, nullptr);
            return true;
          }
          
          else if (card == Card::WINTER) {
            m_Cards.erase(m_Cards.begin() + index);
            m_State->Set(State::WINTER);
            return true;
          }
          return false;
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

Position Player::GetPosition() const{
  return m_Position;
}

bool Player::RetrieveCard(){

  const float scale = CARD_SCALE * GetScreenWidth() * GetScreenHeight() / (CARD_HEIGHT * CARD_WIDTH * 12);
  const float SPACING = CARD_HEIGHT * scale / 2.0;
   
  if (m_Position == Position::BOTTOM_LEFT)
  {
    size_t index = 0;
    for(auto it = m_Row.rbegin(); it != m_Row.rend(); ++it)
    {
      Rectangle LowerLayer = {scale * (CARD_HEIGHT * 2 + 50) + CARD_WIDTH / 2.0f * scale * index , GetScreenHeight() - scale * (CARD_HEIGHT + 50) - SPACING , CARD_WIDTH / 2.0f * scale , SPACING};
      Rectangle UpperLayer = {scale * (CARD_HEIGHT * 2 + 50)+ CARD_WIDTH / 2.0f * scale * index , GetScreenHeight() - scale * (CARD_HEIGHT + 50) - SPACING , CARD_WIDTH * scale , SPACING};
        
      if((CheckCollisionPointRec(GetMousePosition(), LowerLayer) ||
         (CheckCollisionPointRec(GetMousePosition(), UpperLayer) &&
         m_Row.size() - 1 == index )) && 
          IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
      {
        Add(index);
        m_State->Set(State::PLAYING_CARD);
        return true;
      }
      index++;
    }
  }
  
  return false;
}

void Player::Add(size_t index){
  size_t power = m_Row[index].GetPower();
  m_Row.erase(m_Row.begin() + index);

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

Color Player::GetColor() const{
  return m_Color;
}

int Player::CalculateScore(int C) const
{
  int score{};
  int BNum{};

  for(const auto& c : m_Row)
  {
    if (C == c.GetPower())
    {
      BNum++;
    }
    score += c.GetPower();
  }

  if (m_State->GetSeason() == State::Season::WINTER)
  {
    score = m_Row.size();
  }

  if (m_Drummer == true)
  {
    score *= 2;
  }

  if (m_State->GetSeason() == State::Season::SPRING)
  {
     score += BNum * 3;
  }
  score += m_Heroine * 10;
  score += m_Spy;
  
  return score;
}

int Player::GetBiggestNum() const
{
  int BNum{};
  for(const auto& c : m_Row)
  {
    if (BNum < c.GetPower())
    {
      BNum  = c.GetPower();
    }
  }
  return BNum;
}

void Player::Reset()
{
  m_Cards.clear();
  m_Row.clear();
  m_Heroine = 0;
  m_Spy = 0;
  m_Drummer = false;
  m_IsPassed = false;
}

const std::string& Player::GetName() const
{
  return m_Name;
}

void Player::DeleteCard(int BNum)
{
  for (size_t index = 0; index < m_Row.size(); ++index)
  {
    if (m_Row[index].GetPower() == BNum)
    {
      m_Row.erase(m_Row.begin() + index);
    }
  }
}

int Player::GetBishop() const
{
  return m_Bishop;
}
