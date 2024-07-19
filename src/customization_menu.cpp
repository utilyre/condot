#include <raylib.h>

#include <state.hpp>
#include <input.hpp>
#include <customization_menu.hpp>

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

CustomizationMenu::CustomizationMenu(State* state, Event* initiateBattle)
: m_State(state),
  m_InitiateBattleEvent(initiateBattle),
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

  m_MenuButton.Update();
  m_ContinueButton.Update();

  if (m_MenuButton.Pressed())
  {
    m_State->Set(State::MAIN_MENU);
  }
  if (m_ContinueButton.Pressed())
  {
    m_InitiateBattleEvent->Raise(this, nullptr);
    m_State->Set(State::PLACING_BATTLE_MARKER);
  }

  m_IncreasePlayersButton.Update();
  m_DecreasePlayersButton.Update();

  if (m_IncreasePlayersButton.Pressed() && m_PlayerRows.size() < 4)
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
  if (m_DecreasePlayersButton.Pressed() && m_PlayerRows.size() > 3)
  {
    m_PlayerRows.pop_back();
  }

  for (PlayerRow& row : m_PlayerRows)
  {
    row.Name.Update();
    row.Age.Update();
  }
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

  for (const PlayerRow& row : m_PlayerRows)
  {
    row.Name.Render(assets);
    row.Age.Render(assets);
  }
}
