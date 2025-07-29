#pragma once

#include <string>
#include <raylib.h>

#include <asset_manager.hpp>
#include <entity.hpp>

class Input : public Entity
{
public:
  Input(const std::string& placeHolder, Rectangle dimensions);

  void Update() override;
  void Render(const AssetManager& assets) const override;

  const std::string& GetText() const;

  bool Hovered() const;
  bool Focused() const;

private:
  std::string m_PlaceHolder;
  Rectangle m_Dimensions;

  std::string m_Text;
  bool m_Hovered;
  bool m_Focused;
};
