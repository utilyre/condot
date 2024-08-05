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
static const float MAP_SCALE = 0.4f;

Map::Map(State* state)
: m_State(state),
  m_Regions({
    Region("Elinia", Rectangle{34, 24, 127, 259}),
    Region("Rollo", Rectangle{162, 24, 374, 135}),
    Region("Pladaci", Rectangle{540, 27, 234, 176}),
    Region("Bella", Rectangle{777, 25, 240, 197}),
    Region("Talmone", Rectangle{166, 165, 282, 135}),
    Region("Morina", Rectangle{458, 206, 186, 234}),
    Region("Borge", Rectangle{651, 209, 141, 271}),
    Region("Caline", Rectangle{795, 227, 220, 144}),
    Region("Armento", Rectangle{360, 439, 160, 243}),
    Region("Olivadi", Rectangle{520, 474, 107, 308}),
    Region("Dimase", Rectangle{629, 482, 169, 296}),
    Region("Enna", Rectangle{803, 374, 134, 159}),
    Region("Atela", Rectangle{804, 546, 207, 239}),
    Region("Lia", Rectangle{323, 687, 187, 98}),
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
  auto state = m_State->Get();
  if (state != State::PLACING_BATTLE_MARKER &&
      state != State::PLACING_FAVOR_MARKER &&
      state != State::PLAYING_CARD &&
      state != State::SCARECROW)
  {
    return;
  }

  int width = GetScreenWidth();
  int height = GetScreenHeight();

  if ((state == State::PLACING_BATTLE_MARKER ||
       state == State::PLACING_FAVOR_MARKER) &&
      IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
  {
    float scaleFactor = MAP_SCALE * height / MAP_HEIGHT;

    Vector2 mouse = GetMousePosition();
    mouse.x -= (width - scaleFactor * MAP_WIDTH) / 2.0f;
    mouse.y -= (height - scaleFactor * MAP_HEIGHT) / 2.0f;
    mouse.x /= scaleFactor;
    mouse.y /= scaleFactor;

    for (Region& r : m_Regions)
    {
      if (r.CollidesWith(mouse))
      {
        switch (state)
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
  auto state = m_State->Get();
  if (state != State::PLACING_BATTLE_MARKER &&
      state != State::PLACING_FAVOR_MARKER &&
      state != State::PLAYING_CARD &&
      state != State::SCARECROW)
  {
    return;
  }

  int width = GetScreenWidth();
  int height = GetScreenHeight();

  float scaleFactor = MAP_SCALE * height / MAP_HEIGHT;
  float MapPosX = (width - scaleFactor * MAP_WIDTH) / 2.0f;
  float MapPosY = (height - scaleFactor * MAP_HEIGHT) / 2.0f;

  DrawTextureEx(
    assets.Map,
    Vector2{
      MapPosX,
      MapPosY,
    },
    0.0f,
    scaleFactor,
    WHITE
  );

  if(m_BattleMarker)
  {
    DrawCircle(
      MapPosX + (m_BattleMarker->GetRec().x + m_BattleMarker->GetRec().width / 2.0f) * scaleFactor ,
      MapPosY + (m_BattleMarker->GetRec().y + m_BattleMarker->GetRec().height / 2.0f) * scaleFactor ,
      30 * scaleFactor,
      BLACK); 
  }
  
  if(m_FavorMarker)
  {
    DrawCircle(
      MapPosX + (m_FavorMarker->GetRec().x + m_FavorMarker->GetRec().width / 2.0f) * scaleFactor ,
      MapPosY + (m_FavorMarker->GetRec().y + m_FavorMarker->GetRec().height / 2.0f) * scaleFactor ,
      30 * scaleFactor,
      WHITE); 
  }
  
  for (auto& r : m_Regions)
  {
    if(r.GetRuler())
    {
      DrawCircle(
        MapPosX + (r.GetRec().x + r.GetRec().width / 2.0f) * scaleFactor ,
        MapPosY + (r.GetRec().y + r.GetRec().height / 2.0f) * scaleFactor ,
        30 * scaleFactor,
        r.GetRuler()->GetColor()); 
    }
  }
  
  if (state == State::PLACING_BATTLE_MARKER ||
      state == State::PLACING_FAVOR_MARKER)
  {
    const float fontSize = 80.0f;
    const std::string text = "Pick a region";

    DrawTextEx(
      assets.PrimaryFont,
      text.c_str(),
      Vector2{
        (width - 0.3f * fontSize * text.size()) / 2.0f,
        (height + scaleFactor * MAP_HEIGHT + 10.0f) / 2.0f,
      },
      fontSize,
      1,
      BLACK
    );
  }
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
  return AreNeighbors(i, j) && AreNeighbors(i, k) && AreNeighbors(j, k);
}

Region* Map::GetBattleMarker()
{
  return m_BattleMarker;
}

void Map::ResetBattleMarker()
{
  m_BattleMarker = nullptr;
}
