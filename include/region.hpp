#pragma once

#include <string>
#include <raylib.h>

#include <player.hpp>

class Region
{
public:
  explicit Region(const std::string& name, Rectangle collision);

  const std::string& GetName() const;
  const Player* GetRuler() const;
  void SetRuler(Player* ruler);
  bool CollidesWith(Vector2 v) const;
  Rectangle GetRec() const;
private:
  std::string m_Name;
  Rectangle m_Collision;
  Player* m_Ruler;
};
