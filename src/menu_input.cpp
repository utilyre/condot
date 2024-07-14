#include <string>
#include <raylib.h>

#include <asset_manager.hpp>
#include <menu.hpp>

MenuInput::MenuInput(
  const std::string& placeHolder,
  float fontSize,
  float padding,
  Rectangle dimensions
)
: m_PlaceHolder(placeHolder),
  m_FontSize(fontSize),
  m_Padding(padding),
  m_Dimensions(dimensions),
  m_Focused(false)
{
}

void MenuInput::Update()
{
  bool mouseCollides = CheckCollisionPointRec(GetMousePosition(), m_Dimensions);

  SetMouseCursor(mouseCollides ? MOUSE_CURSOR_IBEAM : MOUSE_CURSOR_DEFAULT);
  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
  {
    m_Focused = mouseCollides;
  }

  if (m_Focused)
  {
    int key = GetCharPressed();
    if (key > 0)
      m_Text += key;

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

void MenuInput::Render(const AssetManager& assets) const
{
  DrawRectangleRoundedLines(
    m_Dimensions,
    0.5f,
    0,
    5.0f,
    m_Focused ? RED : BLACK
  );

  DrawTextEx(
    assets.PrimaryFont,
    m_Text.empty() ? m_PlaceHolder.c_str() : m_Text.c_str(),
    Vector2{
      m_Dimensions.x + m_Padding,
      m_Dimensions.y + 0.5f * (m_Dimensions.height - m_FontSize),
    },
    m_FontSize,
    1,
    m_Text.empty() ? GRAY : BLACK
  );
}

std::string MenuInput::GetText() const
{
  return m_Text;
}
