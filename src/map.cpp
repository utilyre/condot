#include <iostream>
#include <vector>
#include <unordered_map>
#include <raylib.h>

#include <asset_manager.hpp>
#include <state.hpp>
#include <map.hpp>
#include <region.hpp>
#include <player.hpp>

static const int MAP_WIDTH = 1057;
static const int MAP_HEIGHT = 831;

Map::Map(State* state)
: m_State(state),
  m_Regions({
    Region("Elinia", Rectangle{28, 20, 103, 210}),
    Region("Rollo", Rectangle{132, 20, 303, 110}),
    Region("Pladaci", Rectangle{438, 22, 190, 143}),
    Region("Bella", Rectangle{630, 21, 195, 160}),
    Region("Talmone", Rectangle{135, 134, 229, 110}),
    Region("Morina", Rectangle{371, 167, 151, 190}),
    Region("Borge", Rectangle{528, 170, 115, 220}),
    Region("Caline", Rectangle{644, 184, 179, 117}),
    Region("Armento", Rectangle{292, 356, 130, 197}),
    Region("Olivadi", Rectangle{422, 384, 87, 250}),
    Region("Dimase", Rectangle{510, 391, 137, 240}),
    Region("Enna", Rectangle{651, 303, 109, 129}),
    Region("Atela", Rectangle{652, 443, 168, 194}),
    Region("Lia", Rectangle{262, 557, 152, 80}),
  }),
  m_Adjacency({
    /*                0  1  2  3  4  5  6  7  8  9 10 11 12 13 */
    /*  0. Elinia  */ 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /*  1. Rollo   */ 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
    /*  2. Pladaci */ 0, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0,
    /*  3. Bella   */ 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0,
    /*  4. Talmone */ 1, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0,
    /*  5. Morina  */ 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0,
    /*  6. Borge   */ 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 0,
    /*  7. Caline  */ 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0,
    /*  8. Armento */ 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1,
    /*  9. Olivadi */ 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 1,
    /* 10. Dimase  */ 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0,
    /* 11. Enna    */ 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0,
    /* 12. Atela   */ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0,
    /* 13. Lia     */ 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0,
  }),
  m_BattleMarker(nullptr),
  m_FavorMarker(nullptr)
{
}

void Map::Update()
{
  int width = GetScreenWidth();
  int height = GetScreenHeight();

  if (
    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
    && (
      m_State->IsPlacingBattleMarker()
      || m_State->IsPlacingFavorMarker()
    )
  )
  {
    Vector2 mouse = GetMousePosition();
    mouse.x -= (width - MAP_WIDTH) / 2.0f;
    mouse.y -= (height - MAP_HEIGHT) / 2.0f;

    for (Region& r : m_Regions)
    {
      if (r.CollidesWith(mouse))
      {
        if (m_State->IsPlacingBattleMarker())
          m_BattleMarker = &r;
        else if (m_State->IsPlacingFavorMarker())
          m_FavorMarker = &r;

        m_State->SetPlaying();
      }
    }

    if (m_BattleMarker)
      std::cout << "Set Battle Marker: " << m_BattleMarker->GetName() << '\n';
    if (m_FavorMarker)
      std::cout << "Set Favor Marker: " << m_FavorMarker->GetName() << '\n';
  }
}

void Map::Render(const AssetManager& assets) const
{
  int width = GetScreenWidth();
  int height = GetScreenHeight();

  DrawTexture(assets.Map, (width - MAP_WIDTH) / 2, (height - MAP_HEIGHT) / 2, WHITE);
}

const Player* Map::FindWinner() const
{
  std::unordered_map<const Player*, std::vector<size_t>> regionIndices;
  for (size_t i = 0; i < m_Regions.size(); i++)
  {
    const Player* ruler = m_Regions[i].GetRuler();
    if (ruler)
    {
      regionIndices[ruler].push_back(i);
    }
  }

  for (const auto& [player, indices] : regionIndices)
  {
    if (indices.size() == 5)
    {
      return player;
    }

    if (
      indices.size() == 3
      && AreNeighbors(indices[0], indices[1], indices[2])
    )
    {
      return player;
    }

    if (
      indices.size() == 4
      && (
        AreNeighbors(indices[0], indices[1], indices[2])
        || AreNeighbors(indices[0], indices[1], indices[3])
        || AreNeighbors(indices[0], indices[2], indices[3])
        || AreNeighbors(indices[1], indices[2], indices[3])
      )
    )
    {
      return player;
    }
  }

  return nullptr;
}

bool Map::AreNeighbors(size_t i, size_t j) const
{
  return m_Adjacency[m_Regions.size() * i + j];
}

bool Map::AreNeighbors(size_t i, size_t j, size_t k) const
{
  return (
    AreNeighbors(i, j)
    || AreNeighbors(i, k)
    || AreNeighbors(j, k)
  );
}
