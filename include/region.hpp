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
  std::optional<PlayerInfo> GetRuler() const;
  void SetRuler(PlayerInfo ruler);
  bool CollidesWith(Vector2 v) const;
  Rectangle GetRec() const;

  static void Serialize(StreamWriter& w, const Region& region);
  static void Deserialize(StreamReader& r, Region& region);

private:
  std::string m_Name;
  Rectangle m_Collision;
  std::optional<PlayerInfo> m_Ruler;
};
