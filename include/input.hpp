#pragma once

#include <string>
#include <raylib.h>

#include <asset_manager.hpp>
#include <entity.hpp>

class Input : public Entity
{
public:
  Input(const std::string& placeHolder, float fontSize, Rectangle dimensions);

  void Update() override;
  void Render(const AssetManager& assets) const override;

  std::string GetText() const;

  bool Hovered() const;
  bool Focused() const;

private:
  std::string m_PlaceHolder;
  float m_FontSize;
  Rectangle m_Dimensions;

  std::string m_Text;
  bool m_Hovered;
  bool m_Focused;
};
