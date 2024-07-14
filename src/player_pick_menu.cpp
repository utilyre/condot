#include <string>
#include <raylib.h>

#include <state.hpp>
#include <menu.hpp>

static const int MENU_WIDTH = 1600;
static const int MENU_HEIGHT = 900;

PlayerPickMenu::PlayerPickMenu(State* state)
: m_State(state),
  m_Padding(50),
  m_Dimensions({
    (GetScreenWidth() - MENU_WIDTH) / 2.0f,
    (GetScreenHeight() - MENU_HEIGHT) / 2.0f,
    MENU_WIDTH,
    MENU_HEIGHT
  })
{
  for (size_t i = 0; i < 3; i++)
  {
    size_t count = m_Rows.size();
    m_Rows.emplace_back(
      MenuInput("Name", 40, 20, Rectangle{m_Dimensions.x + m_Padding, m_Dimensions.y + m_Padding + 120 * (count + 1), 600, 100}),
      MenuInput("Age", 40, 20, Rectangle{m_Dimensions.x + m_Padding + 700, m_Dimensions.y + m_Padding + 120 * (count + 1), 200, 100})
    );
  }
}

void PlayerPickMenu::Update()
{
  if (m_State->Get() != State::PLAYER_PICK_MENU)
  {
    return;
  }

  if (IsKeyPressed(KEY_UP) && m_Rows.size() < 4)
  {
    size_t count = m_Rows.size();
    m_Rows.emplace_back(
      MenuInput("Name", 40, 20, Rectangle{m_Dimensions.x + m_Padding, m_Dimensions.y + m_Padding + 120 * (count + 1), 600, 100}),
      MenuInput("Age", 40, 20, Rectangle{m_Dimensions.x + m_Padding + 700, m_Dimensions.y + m_Padding + 120 * (count + 1), 200, 100})
    );
  }
  if (IsKeyPressed(KEY_DOWN) && m_Rows.size() > 3)
  {
    m_Rows.pop_back();
  }

  for (Row& r : m_Rows)
  {
    r.Name.Update();
    r.Age.Update();
  }
}

void PlayerPickMenu::Render(const AssetManager& assets) const
{
  if (m_State->Get() != State::PLAYER_PICK_MENU)
  {
    return;
  }

  DrawRectangleRounded(m_Dimensions, 0.1f, 0, WHITE);

  DrawTextEx(
    assets.PrimaryFont,
    TextFormat("%d players (use <up> and <down> keys to adjust)", m_Rows.size()),
    Vector2{m_Dimensions.x + m_Padding, m_Dimensions.y + m_Padding},
    50,
    1,
    BLACK
  );

  for (const Row& r : m_Rows)
  {
    r.Name.Render(assets);
    r.Age.Render(assets);
  }
}
