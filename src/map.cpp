#include <raylib.h>

#include <asset_manager.hpp>
#include <map.hpp>
#include <region.hpp>

Map::Map()
: m_Regions({
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
  })
{
}

void Map::Update()
{
}

void Map::Render(const AssetManager& assets) const
{
  int width = GetScreenWidth();
  int height = GetScreenHeight();

  int x = (width - assets.Map.width) / 2;
  int y = (height - assets.Map.height) / 2;

  DrawTexture(assets.Map, x, y, WHITE);

  Vector2 mouse = GetMousePosition();
  mouse.x -= x;
  mouse.y -= y;

  for (const Region& r : m_Regions)
  {
    if (r.CollidesWith(mouse))
    {
      Rectangle collision = r.GetCollision();
      collision.x += x;
      collision.y += y;

      DrawRectangleRec(collision, Color{255, 255, 255, 80});
    }
  }
}
