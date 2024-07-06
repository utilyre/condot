#include <iostream>
#include <raylib.h>

#include <asset_manager.hpp>
#include <state.hpp>
#include <map.hpp>
#include <region.hpp>

static const int MAP_WIDTH = 1057;
static const int MAP_HEIGHT = 831;

Map::Map(State* state)
: m_State(state),
  m_Regions({
    Region("Elinia", Rectangle{28, 20, 103, 210}),
    Region("Rollo", Rectangle{132, 20, 303, 110}),
    Region("Pladaci", Rectangle{438, 22, 190, 143}),
    Region("Pladaci", Rectangle{630, 21, 195, 160}),
    Region("Talmone", Rectangle{135, 134, 229, 110}),
    Region("Morina", Rectangle{371, 167, 151, 190}),
    Region("Borge", Rectangle{528, 170, 115, 220}),
    Region("Caline", Rectangle{644, 184, 179, 117}),
    Region("Armento", Rectangle{292, 356, 130, 197}),
    Region("Olivadi", Rectangle{422, 384, 87, 250}),
    Region("Diamse", Rectangle{510, 391, 137, 240}),
    Region("Enna", Rectangle{651, 303, 109, 129}),
    Region("Antela", Rectangle{652, 443, 168, 194}),
    Region("Lia", Rectangle{262, 557, 152, 80}),
  }),
  m_BattleMarker(nullptr)
{
}

void Map::Update()
{
  int width = GetScreenWidth();
  int height = GetScreenHeight();

  if (m_State->IsRegionPick() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
  {
    Vector2 mouse = GetMousePosition();
    mouse.x -= (width - MAP_WIDTH) / 2.0f;
    mouse.y -= (height - MAP_HEIGHT) / 2.0f;

    for (Region& r : m_Regions)
    {
      if (r.CollidesWith(mouse))
      {
        m_BattleMarker = &r;
        m_State->SetPlaying();
      }
    }
  }
}

void Map::Render(const AssetManager& assets) const
{
  int width = GetScreenWidth();
  int height = GetScreenHeight();

  DrawTexture(assets.Map, (width - MAP_WIDTH) / 2, (height - MAP_HEIGHT) / 2, WHITE);
}
