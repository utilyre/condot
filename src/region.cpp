#include <optional>
#include <string>
#include <raylib.h>

#include <region.hpp>
#include <player.hpp>

Region::Region(const std::string& name, Rectangle collision)
: m_Name(name),
  m_Collision(collision)
{
}

const std::string& Region::GetName() const
{
  return m_Name;
}

std::optional<PlayerLite> Region::GetRuler() const
{
  return m_Ruler;
}

void Region::SetRuler(PlayerLite ruler)
{
  m_Ruler = ruler;
  std::clog << "INFO: " << GetName() << " is conquered by " << ruler.name << '\n';
}

bool Region::CollidesWith(Vector2 v) const
{
  return CheckCollisionPointRec(v, m_Collision);
}

Rectangle Region::GetRec() const
{
  return m_Collision;
}

void Region::Serialize(StreamWriter& w, const Region& region)
{
  w.WriteOptional(region.m_Ruler);
}

void Region::Deserialize(StreamReader& r, Region& region)
{
  r.ReadOptional(region.m_Ruler);
}
