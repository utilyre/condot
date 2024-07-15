#include <raylib.h>

#include <state.hpp>
#include <input.hpp>
#include <customization_menu.hpp>

static const float MENU_WIDTH = 1600.0f;
static const float MENU_HEIGHT = 900.0f;
static const float MENU_ROUNDNESS = 0.1f;
static const float MENU_PADDING = 50.0f;
static const float MENU_SPACING = 120.0f;

static const float TEXT_FONT_SIZE = 50.0f;

static const float INPUT_NAME_WIDTH = 600.0f;
static const float INPUT_NAME_HEIGHT = 100.0f;
static const float INPUT_AGE_WIDTH = 200.0f;
static const float INPUT_AGE_HEIGHT = 100.0f;

CustomizationMenu::CustomizationMenu(State* state)
: m_State(state),
  m_Dimensions({
    (GetScreenWidth() - MENU_WIDTH) / 2.0f,
    (GetScreenHeight() - MENU_HEIGHT) / 2.0f,
    MENU_WIDTH,
    MENU_HEIGHT
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
  if (m_State->Get() != State::PLAYER_PICK_MENU)
  {
    return;
  }

  if (IsKeyPressed(KEY_UP) && m_PlayerRows.size() < 4)
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
  if (IsKeyPressed(KEY_DOWN) && m_PlayerRows.size() > 3)
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
  if (m_State->Get() != State::PLAYER_PICK_MENU)
  {
    return;
  }

  DrawRectangleRounded(m_Dimensions, MENU_ROUNDNESS, 0, WHITE);

  DrawTextEx(
    assets.PrimaryFont,
    TextFormat("%d players", m_PlayerRows.size()),
    Vector2{m_Dimensions.x + MENU_PADDING, m_Dimensions.y + MENU_PADDING},
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
