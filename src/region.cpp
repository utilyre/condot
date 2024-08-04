#include <string>
#include <raylib.h>

#include <region.hpp>
#include <player.hpp>

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

const Player* Region::GetRuler() const
{
  return m_Ruler;
}

void Region::SetRuler(Player* p)
{
  if(p)
  {
    m_Ruler = p;
    std::clog << "INFO: " << GetName() << " is conquered by " << GetRuler()->GetName() << '\n';
  }
}

bool Region::CollidesWith(Vector2 v) const
{
  return CheckCollisionPointRec(v, m_Collision);
}

Rectangle Region::GetRec() const
{
  return m_Collision;
}
