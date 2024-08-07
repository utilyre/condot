#pragma once

#include <string>
#include <optional>
#include <raylib.h>

#include <player.hpp>
#include <stream.hpp>

class Region
{
public:
  explicit Region(const std::string& name, Rectangle collision);

  const std::string& GetName() const;
  std::optional<PlayerLite> GetRuler() const;
  void SetRuler(PlayerLite ruler);
  bool CollidesWith(Vector2 v) const;
  Rectangle GetRec() const;

  static bool Serialize(StreamWriter& w, const Region& region);
  static bool Deserialize(StreamReader& r, Region& region);

private:
  std::string m_Name;
  Rectangle m_Collision;
  std::optional<PlayerLite> m_Ruler;
};
