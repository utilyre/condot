#pragma once

#include <string>

#include <player.hpp>

class Region {
public:
  explicit Region(const std::string& name);

  void SetRuler(const Player* ruler);
  const Player* GetRuler() const;
  const std::string& GetName() const;

private:
  std::string m_Name;

  const Player* m_Ruler;
};
