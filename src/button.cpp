#include <string>
#include <raylib.h>

#include <asset_manager.hpp>
#include <button.hpp>

static const float BUTTON_FONT_SIZE = 50.0f;
static const float BUTTON_ROUNDNESS = 0.5f;
static const Color BUTTON_HOVER_COLOR = {25, 25, 25, 255};

Button::Button(const std::string& text, Rectangle dimensions)
: m_Text(text),
  m_Dimensions(dimensions),
  m_Enabled(true),
  m_Hovered(false)
{
}

void Button::Update()
{
  m_Hovered = m_Enabled &&
    CheckCollisionPointRec(GetMousePosition(), m_Dimensions);
}

void Button::Render(const AssetManager& assets) const
{
  DrawRectangleRounded(
    m_Dimensions,
    BUTTON_ROUNDNESS,
    0,
    m_Enabled ? (m_Hovered ? BUTTON_HOVER_COLOR : BLACK) : Color{20, 20, 20, 180}
  );

  const float textWidth = 0.3f * BUTTON_FONT_SIZE * m_Text.size();
  DrawTextEx(
    assets.PrimaryFont,
    m_Text.c_str(),
    Vector2{
      m_Dimensions.x + 0.5f * (m_Dimensions.width - textWidth),
      m_Dimensions.y + 0.5f * (m_Dimensions.height - BUTTON_FONT_SIZE),
    },
    BUTTON_FONT_SIZE,
    1,
    m_Enabled ? WHITE : Color{255, 255, 255, 180}
  );
}

bool Button::Hovered() const
{
  return m_Hovered;
}

bool Button::Pressed() const
{
  return m_Hovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
}

void Button::Disable()
{
  m_Enabled = false;
}

void Button::Enable()
{
  m_Enabled = true;
}
