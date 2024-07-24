#include <iostream>
#include <vector>
#include <unordered_map>
#include <raylib.h>

#include <asset_manager.hpp>
#include <state.hpp>
#include <map.hpp>
#include <region.hpp>
#include <player.hpp>

static const int MAP_WIDTH = 0.81f * 1057;
static const int MAP_HEIGHT = 0.81f * 831;

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
  if (
    m_State->Get() != State::PLACING_BATTLE_MARKER
    || m_State->Get() != State::PLACING_FAVOR_MARKER)
  {
    return;
  }

  int width = GetScreenWidth();
  int height = GetScreenHeight();

  auto currentState = m_State->Get();
  if (
    IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
    && (
      currentState == State::PLACING_BATTLE_MARKER
      || currentState == State::PLACING_FAVOR_MARKER
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
        switch (currentState)
        {
        case State::PLACING_BATTLE_MARKER:
          m_BattleMarker = &r;
          break;
        case State::PLACING_FAVOR_MARKER:
          m_FavorMarker = &r;
          break;
        default:
          break;
        }

        m_State->Set(State::PLAYING_CARD);
      }
    }

    if (m_BattleMarker)
      std::clog << "INFO: battle marker was set to " << m_BattleMarker->GetName() << '\n';
    if (m_FavorMarker)
      std::clog << "INFO: favor marker was set to " << m_FavorMarker->GetName() << '\n';
  }
}

void Map::Render(const AssetManager& assets) const
{
  if (
    m_State->Get() != State::PLACING_BATTLE_MARKER
    || m_State->Get() != State::PLACING_FAVOR_MARKER)
  {
    return;
  }

  int width = GetScreenWidth();
  int height = GetScreenHeight();

  DrawTexture(assets.Map, (width - MAP_WIDTH) / 2, (height - MAP_HEIGHT) / 2, WHITE);
}

std::vector<const Player*> Map::FindWinners() const
{
  // TEST: this method is NOT tested (at all)
  bool allConquered = true;
  std::unordered_map<const Player*, std::vector<size_t>> regionIndices;
  for (size_t i = 0; i < m_Regions.size(); i++)
  {
    const Player* ruler = m_Regions[i].GetRuler();
    allConquered = allConquered && ruler;
    if (ruler)
    {
      regionIndices[ruler].push_back(i);
    }
  }

  if (allConquered)
  {
    size_t max = 0;
    std::vector<const Player*> winners;
    for (const auto& [player, indices] : regionIndices)
    {
      size_t numIndices = indices.size();
      if (numIndices > max)
      {
        max = numIndices;
        winners.clear();
        winners.push_back(player);
      }
      else if (numIndices == max)
      {
        winners.push_back(player);
      }
    }

    return winners;
  }

  for (const auto& [player, indices] : regionIndices)
  {
    if (
      indices.size() == 5
      || (
        indices.size() == 3
        && AreNeighbors(indices[0], indices[1], indices[2])
      )
      || (
        indices.size() == 4
        && (
          AreNeighbors(indices[0], indices[1], indices[2])
          || AreNeighbors(indices[0], indices[1], indices[3])
          || AreNeighbors(indices[0], indices[2], indices[3])
          || AreNeighbors(indices[1], indices[2], indices[3])
        )
      )
    )
    {
      return std::vector{player};
    }
  }

  return std::vector<const Player*>();
}

bool Map::AreNeighbors(size_t i, size_t j) const
{
  return m_Adjacency[m_Regions.size() * i + j];
}

bool Map::AreNeighbors(size_t i, size_t j, size_t k) const
{
  return AreNeighbors(i, j) || AreNeighbors(i, k) || AreNeighbors(j, k);
}
