#include <string>
#include <raylib.h>

#include <asset_manager.hpp>
#include <button.hpp>

static const float BUTTON_ROUNDNESS = 0.5f;

Button::Button(
  const std::string& text,
  float fontSize,
  Rectangle dimensions
)
: m_Text(text),
  m_FontSize(fontSize),
  m_Dimensions(dimensions),
  m_Hovered(false)
{
}

void Button::Update()
{
  m_Hovered = CheckCollisionPointRec(GetMousePosition(), m_Dimensions);
}

void Button::Render(const AssetManager& assets) const
{
  DrawRectangleRounded(
    m_Dimensions,
    BUTTON_ROUNDNESS,
    0,
    m_Hovered ? Color{25, 25, 25, 255} : BLACK
  );

  const float textWidth = 0.5f * m_FontSize * m_Text.size();
  DrawTextEx(
    assets.PrimaryFont,
    m_Text.c_str(),
    Vector2{
      m_Dimensions.x + 0.5f * (m_Dimensions.width - textWidth),
      m_Dimensions.y + 0.5f * (m_Dimensions.height - m_FontSize),
    },
    m_FontSize,
    1,
    WHITE
  );
}

bool Button::Hovered() const
{
  return m_Hovered;
}

bool Button::Pressed() const
{
  return m_Hovered && IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}
