#pragma once

#include <string>
#include <raylib.h>

#include <asset_manager.hpp>
#include <state.hpp>
#include <entity.hpp>

class MenuButton : public Entity
{
public:
  MenuButton(const std::string& text, float fontSize, Rectangle dimensions);

  void Update() override;
  void Render(const AssetManager& assets) const override;

  bool Hovered() const;

private:
  std::string m_Text;
  float m_FontSize;
  Rectangle m_Dimensions;
  bool m_Hovered;
};

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

  std::string GetText() const;

private:
  std::string m_PlaceHolder;
  std::string m_Text;
  float m_FontSize;
  float m_Padding;
  Rectangle m_Dimensions;
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
  MenuButton m_ButtonStart;
  MenuButton m_ButtonExit;
};

class PlayerPickMenu : public Entity
{
public:
  PlayerPickMenu(State* state);

  void Update() override;
  void Render(const AssetManager& assets) const override;

private:
  State* m_State;
  size_t m_PlayerCount;
};
