#include <stdexcept>
#include <vector>
#include <set>
#include <raylib.h>

#include <state.hpp>
#include <input.hpp>
#include <player.hpp>
#include <customization_menu.hpp>

// #define DEBUG

static const float MENU_WIDTH = 1600.0f;
static const float MENU_HEIGHT = 900.0f;
static const float MENU_ROUNDNESS = 0.1f;
static const float MENU_PADDING = 50.0f;
static const float MENU_SPACING = 120.0f;

static const float BUTTON_NAV_WIDTH = 400.0f;
static const float BUTTON_NAV_HEIGHT = 80.0f;

static const float TEXT_FONT_SIZE = 50.0f;

static const float BUTTON_ADJUST_PLAYERS_WIDTH = 40.0f;
static const float BUTTON_ADJUST_PLAYERS_HEIGHT = 40.0f;

static const float INPUT_NAME_WIDTH = 600.0f;
static const float INPUT_NAME_HEIGHT = 100.0f;
static const float INPUT_AGE_WIDTH = 200.0f;
static const float INPUT_AGE_HEIGHT = 100.0f;

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-const-variable"
static const size_t MIN_PLAYERS = 3;
static const size_t MAX_PLAYERS = 6;
#pragma clang diagnostic pop

static const Color COLORS[6] = {RED, GREEN, BLUE, MAGENTA, GRAY, YELLOW};
static const Position POSITIONS[6] = {
  Position::TOP_LEFT,
  Position::TOP_RIGHT,
  Position::LEFT,
  Position::RIGHT,
  Position::BOTTOM_LEFT,
  Position::BOTTOM_RIGHT,
};

CustomizationMenu::CustomizationMenu(
  State* state,
  Event* initiateBattleEvent,
  Event* addPlayerEvent
) :
  m_State(state),
  m_InitiateBattleEvent(initiateBattleEvent),
  m_AddPlayerEvent(addPlayerEvent),
  m_Dimensions({
    (GetScreenWidth() - MENU_WIDTH) / 2.0f,
    (GetScreenHeight() - MENU_HEIGHT) / 2.0f,
    MENU_WIDTH,
    MENU_HEIGHT
  }),
  m_MenuButton("Back to Menu", Rectangle{
    m_Dimensions.x + MENU_PADDING,
    m_Dimensions.y - MENU_PADDING,
    BUTTON_NAV_WIDTH,
    BUTTON_NAV_HEIGHT,
  }),
  m_ContinueButton("Continue", Rectangle{
    m_Dimensions.x + MENU_WIDTH - BUTTON_NAV_WIDTH - MENU_PADDING,
    m_Dimensions.y - MENU_PADDING,
    BUTTON_NAV_WIDTH,
    BUTTON_NAV_HEIGHT,
  }),
  m_IncreasePlayersButton("+", Rectangle{
    m_Dimensions.x + MENU_PADDING,
    m_Dimensions.y + MENU_PADDING,
    BUTTON_ADJUST_PLAYERS_WIDTH,
    BUTTON_ADJUST_PLAYERS_HEIGHT,
  }),
  m_DecreasePlayersButton("-", Rectangle{
    m_Dimensions.x + MENU_PADDING,
    m_Dimensions.y + MENU_PADDING + BUTTON_ADJUST_PLAYERS_HEIGHT,
    BUTTON_ADJUST_PLAYERS_WIDTH,
    BUTTON_ADJUST_PLAYERS_HEIGHT,
  })
{
  for (size_t i = 0; i < 3; i++)
  {
    m_PlayerRows.emplace_back(
      Input("Name", Rectangle{
        m_Dimensions.x + MENU_PADDING,
        m_Dimensions.y + MENU_PADDING + MENU_SPACING * (i + 1),
        INPUT_NAME_WIDTH,
        INPUT_NAME_HEIGHT
      }),

      Input("Age", Rectangle{
        m_Dimensions.x + MENU_PADDING + INPUT_NAME_WIDTH + MENU_SPACING,
        m_Dimensions.y + MENU_PADDING + MENU_SPACING * (i + 1),
        INPUT_AGE_WIDTH,
        INPUT_AGE_HEIGHT
      })
    );
  }
}

void CustomizationMenu::Update()
{
  if (m_State->Get() != State::CUSTOMIZATION_MENU)
  {
    return;
  }

#ifdef DEBUG
  m_AddPlayerEvent->Notify(this, PlayerInfo("Jane", 1, COLORS[0], POSITIONS[0]));
  m_AddPlayerEvent->Notify(this, PlayerInfo("Aria", 2, COLORS[1], POSITIONS[1]));
  m_AddPlayerEvent->Notify(this, PlayerInfo("Theo", 3, COLORS[2], POSITIONS[2]));
  m_AddPlayerEvent->Notify(this, PlayerInfo("Milo", 4, COLORS[3], POSITIONS[3]));
  m_AddPlayerEvent->Notify(this, PlayerInfo("Alex", 5, COLORS[4], POSITIONS[4]));
  m_AddPlayerEvent->Notify(this, PlayerInfo("John", 6, COLORS[5], POSITIONS[5]));

  m_InitiateBattleEvent->Notify(this);
  m_State->Set(State::PLACING_BATTLE_MARKER);
#else
  m_MenuButton.Update();
  m_ContinueButton.Update();

  if (m_MenuButton.Pressed())
  {
    m_State->Set(State::MAIN_MENU);
  }
  if (m_ContinueButton.Pressed())
  {
    Continue();
  }

  m_IncreasePlayersButton.Update();
  m_DecreasePlayersButton.Update();

  if (m_IncreasePlayersButton.Pressed() && m_PlayerRows.size() < MAX_PLAYERS)
  {
    size_t len = m_PlayerRows.size();
    m_PlayerRows.emplace_back(
      Input("Name", Rectangle{
        m_Dimensions.x + MENU_PADDING,
        m_Dimensions.y + MENU_PADDING + MENU_SPACING * (len + 1),
        INPUT_NAME_WIDTH,
        INPUT_NAME_HEIGHT
      }),

      Input("Age", Rectangle{
        m_Dimensions.x + MENU_PADDING + INPUT_NAME_WIDTH + MENU_SPACING,
        m_Dimensions.y + MENU_PADDING + MENU_SPACING * (len + 1),
        INPUT_AGE_WIDTH,
        INPUT_AGE_HEIGHT
      })
    );
  }
  if (m_DecreasePlayersButton.Pressed() && m_PlayerRows.size() > MIN_PLAYERS)
  {
    m_PlayerRows.pop_back();
  }

  for (PlayerRow& row : m_PlayerRows)
  {
    row.Name.Update();
    row.Age.Update();
  }
#endif
}

void CustomizationMenu::Render(const AssetManager& assets) const
{
  if (m_State->Get() != State::CUSTOMIZATION_MENU)
  {
    return;
  }

  DrawRectangleRounded(m_Dimensions, MENU_ROUNDNESS, 0, RAYWHITE);

  m_MenuButton.Render(assets);
  m_ContinueButton.Render(assets);

  m_IncreasePlayersButton.Render(assets);
  m_DecreasePlayersButton.Render(assets);

  DrawTextEx(
    assets.PrimaryFont,
    TextFormat("%d players", m_PlayerRows.size()),
    Vector2{
      m_Dimensions.x + MENU_PADDING + BUTTON_ADJUST_PLAYERS_WIDTH + 0.25f * MENU_SPACING,
      m_Dimensions.y + MENU_PADDING + BUTTON_ADJUST_PLAYERS_HEIGHT - 0.5f * TEXT_FONT_SIZE,
    },
    TEXT_FONT_SIZE,
    1,
    BLACK
  );

  DrawTextEx(
    assets.PrimaryFont,
    m_ErrorMsg.c_str(),
    Vector2{
      m_Dimensions.x + 0.5f * MENU_WIDTH - 0.15f * TEXT_FONT_SIZE * m_ErrorMsg.size(),
      m_Dimensions.y + MENU_PADDING,
    },
    TEXT_FONT_SIZE,
    1,
    RED
  );

  for (const PlayerRow& row : m_PlayerRows)
  {
    row.Name.Render(assets);
    row.Age.Render(assets);
  }
}

void CustomizationMenu::Continue()
{
  std::vector<PlayerInfo> players;

  std::set<std::string> names;

  for (const PlayerRow& row : m_PlayerRows)
  {
    const std::string& name = row.Name.GetText();
    if (name.empty())
    {
      m_ErrorMsg = "Please fill out all name inputs.";
      return;
    }
    
    if (name.size() > 40)
    {
      m_ErrorMsg = "Please choose shorter name.";
      return;
    }
    
    if (names.count(name))
    {
      m_ErrorMsg = "Please avoid duplicated names.";
      return;
    }
     
    for (const int c : name) 
    {
      if(c >= 48 && c <= 57)
      {
        m_ErrorMsg = "Name should not contain digits.";
        return;
      }
      else if (!(c >= 65 && c <= 90) &&
               !(c >= 97 && c <= 122) &&
               !(c == 32)) 
      {
        m_ErrorMsg = "Invalid Name.";
        return;
      }
    }
    names.insert(name);

    const std::string& ageStr = row.Age.GetText();
    if (ageStr.empty())
    {
      m_ErrorMsg = "Please fill out all age inputs.";
      return;
    }

    try
    {
      int age = std::stoi(ageStr);
      if (age <= 0)
      {
        m_ErrorMsg = "Please enter a positive age.";
        return;
      }
      else if (age > 100) 
      {
        m_ErrorMsg = "Please enter an age below 100.";
        return;
      }

      players.emplace_back(
        name,
        age,
        COLORS[players.size()],
        POSITIONS[players.size()]
      );
    }
    catch (const std::invalid_argument&)
    {
      m_ErrorMsg = "Please enter a valid age.";
      return;
    }
  }

  for (PlayerInfo player : players)
  {
    m_AddPlayerEvent->Notify(this, player);
  }
  m_InitiateBattleEvent->Notify(this);
  m_State->Set(State::PLACING_BATTLE_MARKER);
}
