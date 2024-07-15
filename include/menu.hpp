#pragma once

#include <string>
#include <vector>
#include <raylib.h>

#include <asset_manager.hpp>
#include <state.hpp>
#include <entity.hpp>
#include <button.hpp>

class MenuInput : public Entity
{
public:
  MenuInput(
    const std::string& placeHolder,
    float fontSize,
    float padding,
    Rectangle dimensions
  );

  void Update() override;
  void Render(const AssetManager& assets) const override;

  bool IsHovered() const;
  bool IsFocused() const;
  std::string GetText() const;

private:
  std::string m_PlaceHolder;
  std::string m_Text;
  float m_FontSize;
  float m_Padding;
  Rectangle m_Dimensions;
  bool m_Hovered;
  bool m_Focused;
};

class StartMenu : public Entity
{
public:
  StartMenu(State* state);

  void Update() override;
  void Render(const AssetManager& assets) const override;

private:
  State* m_State;
  Button m_ButtonStart;
  Button m_ButtonExit;
};

class PlayerPickMenu : public Entity
{
public:
  PlayerPickMenu(State* state);

  void Update() override;
  void Render(const AssetManager& assets) const override;

private:
  struct Row {
    MenuInput Name;
    MenuInput Age;
  };

private:
  State* m_State;
  float m_Padding;
  Rectangle m_Dimensions;
  std::vector<Row> m_Rows;
};
