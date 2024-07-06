#include <string>
#include <raylib.h>

#include <region.hpp>

Region::Region(const std::string& name, Rectangle collision)
: m_Name(name),
  m_Collision(collision),
  m_Ruler(nullptr)
{
}

const std::string& Region::GetName() const
{
  return m_Name;
}

bool Region::CollidesWith(Vector2 v) const
{
  return (
    v.x > m_Collision.x
    && v.x < m_Collision.x + m_Collision.width
    && v.y > m_Collision.y
    && v.y < m_Collision.y + m_Collision.height
  );
}
