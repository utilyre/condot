#include <string>
#include <raylib.h>

#include <asset_manager.hpp>
#include <button.hpp>

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
  Color background = BLACK;
  Color foreground = WHITE;

  if (m_Hovered)
  {
    background = Color{25, 25, 25, 255};
  }

  DrawRectangleRounded(m_Dimensions, 0.5f, 0, background);
  DrawTextEx(
    assets.PrimaryFont,
    m_Text.c_str(),
    Vector2{
      m_Dimensions.x + 0.5f * m_Dimensions.width - 0.25f * m_FontSize * m_Text.size(),
      m_Dimensions.y + 0.5f * (m_Dimensions.height - m_FontSize),
    },
    m_FontSize,
    1,
    foreground
  );
}

bool Button::Hovered() const
{
  return m_Hovered;
}
