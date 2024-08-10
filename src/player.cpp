#include <cmath>
#include <raylib.h>

#include <math.h>
#include <asset_manager.hpp>
#include <state.hpp>
#include <event.hpp>
#include <player.hpp>
#include <card.hpp>
#include <mercenary.hpp>
#include <button.hpp>
#include <season.hpp>
#include <vector>

#define MAX(a, b) ((a)>(b)? (a) : (b))
#define MIN(a, b) ((a)<(b)? (a) : (b))

static const int CardWidth = 164;
static const int CardHeight = 255;
static const float CardScale = 0.15f;

Player::Player()
: m_PassButton ("SURRENDER",Rectangle(10,GetScreenHeight() - 100 , 170 , 90)),
  m_RevealCardsButton("Reveal", Rectangle{10, GetScreenHeight() - 200.0f, 170, 90})
{
}

Player::Player(
  const std::string& name,
  int age,
  Color color,
  Position position
)
: m_Name(name),
  m_Color(color),
  m_Age(age),
  m_Position(position),
  m_IsPassed(false),
  m_Spy(0),
  m_Heroine(0),
  m_Drummer(false),
  m_Bishop(0),
  m_PassButton ("SURRENDER",Rectangle(10,GetScreenHeight() - 100 , 170 , 90)),
  m_RevealCardsButton("Reveal", Rectangle{10, GetScreenHeight() - 200.0f, 170, 90})
{
}

void Player::Init(
  State* state,
  Season* season,
  bool* hideCards,
  Event* rotateTurnEvent,
  Event* restartBattleEvent,
  Event* takeFavorMarkerEvent
)
{
  m_State = state;
  m_Season = season;
  m_HideCards = hideCards;
  m_RotateTurnEvent = rotateTurnEvent;
  m_RestartBattleEvent = restartBattleEvent;
  m_TakeFavorMarkerEvent = takeFavorMarkerEvent;
}

void Player::Update()
{
  auto state = m_State->Get();

  if (state != State::PLAYING_CARD &&
      state != State::SCARECROW){
    return;
  }
    bool RotateStatus = false;

  if (m_Position == Position::BOTTOM_LEFT)
  {
    m_PassButton.Update();  

    if (*m_HideCards)
    {
      m_RevealCardsButton.Update();
      if (m_RevealCardsButton.Pressed())
      {
        *m_HideCards = false;
      }
    }
  }

    if(state == State::PLAYING_CARD)
      RotateStatus = PlayCard();
    
    else if (m_State->Get() == State::SCARECROW)
      RotateStatus = RetrieveCard();
    
    if(RotateStatus == true && m_State->Get() == State::PLAYING_CARD)
    {
      bool PassStatus = false;
      bool PlayStatus = true;
      if(IsPassed())
      {
        m_IsPassed = PassStatus;
        m_RotateTurnEvent->Notify(this, &PassStatus);
        m_IsPassed = PassStatus;
      }
      else
      {
        m_RotateTurnEvent->Notify(this, &PlayStatus);
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
  
 const float Width  = GetScreenWidth();
 const float Height = GetScreenHeight();
 
 const float Scale = MIN((Width / CardWidth), (Height / CardHeight)) * CardScale;
 const float THICKNESS = Scale * CardHeight * 1.1f;
 const float Spacing = Scale * (9 * CardWidth / 2.0f + CardWidth); 

 const Vector2 BottomLeft  {(Width / 2.0f) - (Spacing * 1.1f), Height - (CardHeight * Scale) * 1.3f};
 const Vector2 BottomRight {(Width / 2.0f) * 1.1f, Height - (CardHeight * Scale) * 1.3f};
 
 const Vector2 TopLeft {(Width / 2.0f) - (Spacing * 1.1f) + Spacing, (CardHeight * Scale) * 1.3f};
 const Vector2 TopRight {(Width / 2.0f) * 1.1f + Spacing, (CardHeight * Scale) * 1.3f};
 
 const Vector2 Left {(CardHeight * Scale) * 1.3f, (Height - Spacing) / 2.0f};
 const Vector2 Right {Width - (CardHeight * Scale) * 1.3f, (Height + Spacing) / 2.0f};
   
  switch (m_Position)
  {
  case Position::TOP_LEFT:
    DrawRectangle(TopLeft.x - Spacing, 0 , Spacing , THICKNESS , m_Color);
    RenderRows(assets, Vector2{TopLeft.x , TopLeft.y + CardHeight * Scale / 2}, 180, Scale);
    RenderCards(assets, TopLeft ,180, Scale);
    DrawText(m_Name.c_str(), (TopLeft.x - Spacing) + Spacing / 2.0f * 0.9, 10, 30, BLACK);
    break;
    
  case Position::TOP_RIGHT:
    DrawRectangle(TopRight.x - Spacing, 0 , Spacing , THICKNESS , m_Color);
    RenderRows(assets,Vector2{TopRight.x , TopRight.y + CardHeight * Scale / 2} , 180, Scale);
    RenderCards(assets, TopRight, 180, Scale);
    DrawText(m_Name.c_str(), (TopRight.x - Spacing) + Spacing / 2.0f * 0.9, 10, 30, BLACK);
    break;
    
  case Position::BOTTOM_LEFT:
    DrawRectangle(BottomLeft.x, Height - THICKNESS , Spacing , THICKNESS , m_Color);
    RenderRows (assets , Vector2{ BottomLeft.x , BottomLeft.y - CardHeight * Scale / 2} , 0, Scale);

    if (*m_HideCards)
    {
      m_RevealCardsButton.Render(assets);
    }
    else
    {
      m_PassButton.Render(assets);
    }

    RenderCards(assets , BottomLeft , 0, Scale);
    DrawText(m_Name.c_str(), BottomLeft.x + Spacing / 2.0f * 0.9f, BottomLeft.y + CardHeight * Scale, 30, BLACK);
  
    break;
    
  case Position::BOTTOM_RIGHT:
    DrawRectangle(BottomRight.x, Height - THICKNESS , Spacing , THICKNESS , m_Color);
    RenderRows (assets , Vector2{ BottomRight.x , BottomRight.y - CardHeight * Scale / 2} , 0, Scale);
    RenderCards(assets , BottomRight , 0, Scale);
    DrawText(m_Name.c_str(), BottomRight.x + Spacing / 2.0f * 0.9f, BottomLeft.y + CardHeight * Scale, 30, BLACK);
    break;
    
  case Position::RIGHT:
    DrawRectangle(Right.x, Right.y - Spacing , Spacing , Spacing , m_Color);
    RenderRows (assets , Vector2{ Right.x - CardHeight * Scale / 2, Right.y} , 270, Scale);
    RenderCards(assets , Right , 270, Scale);
    DrawTextPro(
      assets.PrimaryFont,
      m_Name.c_str(),
      Vector2{Right.x + CardHeight * Scale, GetScreenHeight() / 2.0f + 20}, 
      Vector2{0,0}, 
      270, 
      40, 
      12,
      BLACK 
    );
    break;
    
  case Position::LEFT:
    DrawRectangle(0, Left.y, THICKNESS  , Spacing , m_Color);
    RenderRows (assets , Vector2{ Left.x + CardHeight * Scale / 2 , Left.y} , 90, Scale);
    RenderCards(assets , Left, 90, Scale);
    DrawTextPro(
      assets.PrimaryFont,
      m_Name.c_str(),
      Vector2{Left.x - CardHeight * Scale, GetScreenHeight() / 2.0f - 20}, 
      Vector2{0,0}, 
      90, 
      40, 
      12,
      BLACK 
    );

    break;
  }
}

void Player::RenderRows(const AssetManager& assets, Vector2 cordinate, float rotation, float ratio) const
{
 const float Width  = GetScreenWidth();
 const float Height = GetScreenHeight();
 
 const float Scale = MIN((Width / CardWidth), (Height / CardHeight)) * CardScale;

  if (m_Position == Position::TOP_LEFT)
  {
    for (auto c = m_Row.rbegin(); c != m_Row.rend(); ++c)
    {
      DrawTextureEx(c->GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x -= CardWidth / 2.0 * Scale;
    }
  }
  
  if (m_Position == Position::TOP_RIGHT)
  {
    for (auto c = m_Row.rbegin(); c != m_Row.rend(); ++c)
    {
      DrawTextureEx(c->GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x -= CardWidth / 2.0 * Scale;
    }
  }
  
  if (m_Position == Position::BOTTOM_LEFT)
  {
    for(const auto& c : m_Row)
    {
      DrawTextureEx(c.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x += CardWidth / 2.0 * Scale;
    }
  }

  if (m_Position == Position::BOTTOM_RIGHT)
  {
    for (const auto& c : m_Row)
    {
      DrawTextureEx(c.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x += CardWidth / 2.0 * Scale;
    }
    
  }
  
  if (m_Position == Position::LEFT)
  {
    for (const auto& c : m_Row)
    {
      DrawTextureEx(c.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.y += CardWidth / 2.0 * Scale;
    }
  }

  if (m_Position == Position::RIGHT)
  {
    for(auto c = m_Row.rbegin(); c != m_Row.rend(); ++c)
    {
      DrawTextureEx(c->GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.y -= CardWidth / 2.0 * Scale;
      
    }  
  }
}

void Player::RenderCards(const AssetManager& assets, Vector2 cordinate, float rotation, float ratio) const
{
 const float Width  = GetScreenWidth();
 const float Height = GetScreenHeight();  
 const float Scale = MIN((Width / CardWidth), (Height / CardHeight)) * CardScale;
 
   
  Card card = Card::BACKSIDE;
  if (m_Position == Position::TOP_LEFT)
  {
    for (size_t c{} ; c < m_Cards.size() ; ++c)
    {
      DrawTextureEx(card.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x -= CardWidth / 2.0 * Scale;
    }
  }

  if (m_Position == Position::TOP_RIGHT)
  {
    for (size_t c{} ; c < m_Cards.size() ; ++c)
    {
      DrawTextureEx(card.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x -= CardWidth / 2.0 * Scale;
    }
  }
  
  if (m_Position == Position::BOTTOM_LEFT)
  {
    for (const auto& c : m_Cards)
    {
      DrawTextureEx(
        *m_HideCards ? card.GetAsset(assets) : c.GetAsset(assets),
        cordinate,
        rotation,
        ratio,
        WHITE
      );
      cordinate.x += CardWidth / 2.0 * Scale;
    }
    
  }
  
  if (m_Position == Position::BOTTOM_RIGHT)
  {
    for (size_t c{}; c < m_Cards.size(); ++c)
    {
      DrawTextureEx(card.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.x += CardWidth / 2.0 * Scale;
    }
    
  }
  if (m_Position == Position::LEFT)
  {
    for (size_t c{} ; c < m_Cards.size(); ++c)
    {
      DrawTextureEx(card.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.y += CardWidth / 2.0 * Scale;
    }
  }
  
  if (m_Position == Position::RIGHT)
  {
    for(size_t c{} ; c < m_Cards.size() ; ++c)
    {
      DrawTextureEx(card.GetAsset(assets), cordinate, rotation, ratio, WHITE);
      cordinate.y -= CardWidth / 2.0 * Scale;
      
    }  
  }
}

bool Player::PlayCard(){

  const float Width  = GetScreenWidth();
  const float Height = GetScreenHeight();
  const float scale = MIN((Width / CardWidth), (Height / CardHeight)) * CardScale;
  const float Spacing = scale * (9 * CardWidth / 2.0f + CardWidth); 
  const Vector2 BottomLeft  {(Width / 2.0f) - (Spacing * 1.1f), Height - (CardHeight * scale) * 1.3f};
  
  if (!*m_HideCards && m_Position == Position::BOTTOM_LEFT)
  {
    size_t index = 0;
    for(auto it = m_Cards.rbegin(); it != m_Cards.rend(); ++it)
    {
      Rectangle LowerLayer = {BottomLeft.x + CardWidth / 2.0f * scale * index , BottomLeft.y, CardWidth / 2.0f * scale , CardHeight * scale};
      Rectangle UpperLayer = {BottomLeft.x + CardWidth / 2.0f * scale * index , BottomLeft.y, CardWidth * scale , CardHeight * scale};
        
      if((CheckCollisionPointRec(GetMousePosition(), LowerLayer) ||
         (CheckCollisionPointRec(GetMousePosition(), UpperLayer) &&
         m_Cards.size() - 1 == index )) && 
          IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
      {
        bool status = PickCard(index);
        if (status) *m_HideCards = true;
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
  
  else if (card == Card::BISHOP) {
    m_Cards.erase(m_Cards.begin() + index);
    m_Bishop++;
    m_TakeFavorMarkerEvent->Notify(this);
    return true;
  }
  
  else if (card == Card::DRUMMER) {
    m_Cards.erase(m_Cards.begin() + index);
    m_Drummer++;
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
    *m_Season = Season::SPRING;
    return true;
  }
  
  else if (card == Card::SPY) {
    m_Cards.erase(m_Cards.begin() + index);
    m_Spy++;
    return true;
  }
  
  else if (card == Card::TURNCOAT) {
    m_Cards.erase(m_Cards.begin() + index);
    m_RestartBattleEvent->Notify(this, nullptr);
    return true;
  }
  
  else if (card == Card::WINTER) {
    m_Cards.erase(m_Cards.begin() + index);
    *m_Season = Season::WINTER;
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

  const float Width  = GetScreenWidth();
  const float Height = GetScreenHeight();
  const float scale = MIN((Width / CardWidth), (Height / CardHeight)) * CardScale;
  const float Spacing = scale * (9 * CardWidth / 2.0f + CardWidth); 
  const Vector2 BottomLeft  {(Width / 2.0f) - (Spacing * 1.1f), Height - (CardHeight * scale) * 1.3f - (scale * (CardHeight / 2.0f))};
  
  if (m_Position == Position::BOTTOM_LEFT)
  {
    size_t index = 0;
    for(auto it = m_Row.rbegin(); it != m_Row.rend(); ++it)
    {
      Rectangle LowerLayer = {BottomLeft.x + CardWidth / 2.0f * scale * index , BottomLeft.y, CardWidth / 2.0f * scale , CardHeight / 2.0f * scale};
      Rectangle UpperLayer = {BottomLeft.x + CardWidth / 2.0f * scale * index , BottomLeft.y, CardWidth * scale, CardHeight / 2.0f * scale};
        
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
  m_Bishop = 0;
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

  if (*m_Season == Season::WINTER)
  {
    score = 0;
    for (auto& c : m_Row) 
    {
      score += floor(c.GetPower() / 2);
    }
  }

  if (m_Drummer > 0)
  {
    score *= pow(1.5,m_Drummer);
    score = floor(score);
  }

  if (*m_Season == Season::SPRING)
  {
    score += BNum * 3;
    score += m_Heroine * 3;
  }

  
  score += m_Heroine * 10;
  score += m_Spy;
  
  return score;
}

int Player::GetDrummer() const
{
  return m_Drummer;
}

int Player::GetHeroine() const
{
  return m_Heroine;
}

int Player::GetBishop() const
{
  return m_Bishop;
}

int Player::GetSpy() const
{
  return m_Spy;
}

void Player::DecreaseBishop()
{
  m_Bishop--;
}
void Player::Serialize(StreamWriter& w, const Player& player)
{
  w.WriteString(player.m_Name);
  w.WriteRaw(player.m_Age);
  w.WriteRaw(player.m_Color);
  w.WriteRaw(player.m_Position);
  w.WriteVector(player.m_Cards);
  w.WriteVector(player.m_Row);
  w.WriteRaw(player.m_IsPassed);
  w.WriteRaw(player.m_Spy);
  w.WriteRaw(player.m_Heroine);
  w.WriteRaw(player.m_Drummer);
  w.WriteRaw(player.m_Bishop);
}

void Player::Deserialize(StreamReader& r, Player& player)
{
  r.ReadString(player.m_Name);
  r.ReadRaw(player.m_Age);
  r.ReadRaw(player.m_Color);
  r.ReadRaw(player.m_Position);
  r.ReadVector(player.m_Cards);
  r.ReadVector(player.m_Row);
  r.ReadRaw(player.m_IsPassed);
  r.ReadRaw(player.m_Spy);
  r.ReadRaw(player.m_Heroine);
  r.ReadRaw(player.m_Drummer);
  r.ReadRaw(player.m_Bishop);
}

PlayerInfo::PlayerInfo(
  const std::string& name,
  int age,
  Color color,
  Position position
)
: name(name),
  age(age),
  color(color),
  position(position)
{
}

PlayerInfo::PlayerInfo(const Player& player)
: name(player.GetName()),
  age(player.GetAge()),
  color(player.GetColor()),
  position(player.GetPosition())
{
}

bool PlayerInfo::operator==(const PlayerInfo& other) const
{
  return name == other.name;
}

void PlayerInfo::Serialize(StreamWriter& w, const PlayerInfo& player)
{
  w.WriteString(player.name);
  w.WriteRaw(player.age);
  w.WriteRaw(player.color);
  w.WriteRaw(player.position);
}

void PlayerInfo::Deserialize(StreamReader& r, PlayerInfo& player)
{
  r.ReadString(player.name);
  r.ReadRaw(player.age);
  r.ReadRaw(player.color);
  r.ReadRaw(player.position);
}

const std::vector<Mercenary>& Player::GetRow() const
{
  return m_Row;
}
