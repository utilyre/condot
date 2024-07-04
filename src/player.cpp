#include <asset_manager.hpp>
#include <player.hpp>

Player::Player(const std::string& name, Color color, Position position)
: m_Name(name),
  m_Color(color),
  m_Position(position)
{}

void Player::Update()
{
}

void Player::Render(const AssetManager& assets) const
{
  int monitor = GetCurrentMonitor();
  int width = GetMonitorWidth(monitor);
  int height = GetMonitorHeight(monitor);

  int length = 3 * height / 4;
  int thickness = 200;

  switch (m_Position)
  {
  case Position::TOP:
    DrawRectangle((width - length) / 2, 0, length, thickness, RED);
    break;
  case Position::RIGHT:
    DrawRectangle(width - thickness, (height - length) / 2, thickness, length, GREEN);
    break;
  case Position::BOTTOM:
    DrawRectangle((width - length) / 2, height - thickness, length, thickness, BLUE);
    break;
  case Position::LEFT:
    DrawRectangle(0, (height - length) / 2, thickness, length, GRAY);
    break;
  }
}
