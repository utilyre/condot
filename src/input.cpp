#include <string>
#include <raylib.h>

#include <asset_manager.hpp>
#include <input.hpp>

static const float INPUT_ROUNDNESS = 0.5f;
static const float INPUT_BORDER_THICKNESS = 5.0f;
static const float INPUT_PADDING = 20.0f;

Input::Input(
  const std::string& placeHolder,
  float fontSize,
  Rectangle dimensions
)
: m_PlaceHolder(placeHolder),
  m_FontSize(fontSize),
  m_Dimensions(dimensions),
  m_Hovered(false),
  m_Focused(false)
{
}

void Input::Update()
{
  bool prevHovered = m_Hovered;
  m_Hovered = CheckCollisionPointRec(GetMousePosition(), m_Dimensions);

  if (prevHovered && !m_Hovered)
  {
    SetMouseCursor(MOUSE_CURSOR_DEFAULT);
  }
  else if (!prevHovered && m_Hovered)
  {
    SetMouseCursor(MOUSE_CURSOR_IBEAM);
  }

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
  {
    m_Focused = m_Hovered;
  }

  if (m_Focused)
  {
    int key = GetCharPressed();
    if (key > 0)
    {
      m_Text += key;
    }

    if (
      !m_Text.empty()
      && (
        IsKeyPressed(KEY_BACKSPACE)
        || IsKeyPressedRepeat(KEY_BACKSPACE)
      )
    )
    {
      m_Text.pop_back();
    }
  }
}

void Input::Render(const AssetManager& assets) const
{
  DrawRectangleRoundedLines(
    m_Dimensions,
    INPUT_ROUNDNESS,
    0,
    INPUT_BORDER_THICKNESS,
    m_Focused ? RED : BLACK
  );

  DrawTextEx(
    assets.PrimaryFont,
    m_Text.empty() ? m_PlaceHolder.c_str() : m_Text.c_str(),
    Vector2{
      m_Dimensions.x + INPUT_PADDING,
      m_Dimensions.y + 0.5f * (m_Dimensions.height - m_FontSize),
    },
    m_FontSize,
    1,
    m_Text.empty() ? GRAY : BLACK
  );
}

bool Input::Hovered() const
{
  return m_Hovered;
}

bool Input::Focused() const
{
  return m_Focused;
}

std::string Input::GetText() const
{
  return m_Text;
}
