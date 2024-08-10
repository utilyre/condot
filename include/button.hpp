#pragma once

#include <string>
#include <raylib.h>

#include <asset_manager.hpp>
#include <entity.hpp>

class Button : public Entity
{
public:
  Button(const std::string& text, Rectangle dimensions);

  void Update() override;
  void Render(const AssetManager& assets) const override;

  bool Hovered() const;
  bool Pressed() const;

  void Disable();
  void Enable();

private:
  std::string m_Text;
  Rectangle m_Dimensions;

  bool m_Enabled;
  bool m_Hovered;
};
