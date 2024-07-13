#pragma once

#include <string>
#include <raylib.h>

#include <asset_manager.hpp>
#include <entity.hpp>

class MenuButton : public Entity
{
public:
  MenuButton(const std::string& text, float fontSize, Rectangle dimensions);

  void Update() override;
  void Render(const AssetManager&) const override;

  bool Hovered() const;

private:
  std::string m_Text;
  float m_FontSize;
  Rectangle m_Dimensions;
  bool m_Hovered;
};
