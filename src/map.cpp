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

Map::Map(
  State* state,
  const std::vector<Player>* players,
  size_t* turn,
  ssize_t* favorMarkerChooserIndex
)
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
  m_BattleMarkerIndex(-1),
  m_FavorMarkerIndex(-1),
  m_Players(players),
  m_Turn(turn),
  m_FavorMarkerChooserIndex(favorMarkerChooserIndex)
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

    for (size_t i = 0; i < m_Regions.size(); i++)
    {
      if (!m_Regions[i].CollidesWith(mouse) ||
          m_Regions[i].GetRuler().has_value() ||
          ssize_t(i) == m_FavorMarkerIndex)
      {
        continue;
      }

      if (state == State::PLACING_BATTLE_MARKER)
      {
        m_BattleMarkerIndex = i;
        m_State->Set(State::PLAYING_CARD);
      }
      else if (state == State::PLACING_FAVOR_MARKER)
      {
        m_FavorMarkerIndex = i;
        *m_FavorMarkerChooserIndex = -1;
        m_State->Set(State::PLACING_BATTLE_MARKER);
      }

      if (const Region* bm = GetBattleMarker())
        std::clog << "INFO: battle marker was set to " << bm->GetName() << '\n';
      if (const Region* fm = GetFavorMarker())
        std::clog << "INFO: favor marker was set to " << fm->GetName() << '\n';

      break;
    }
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

  if (const Region* bm = GetBattleMarker())
  {
    DrawCircle(
      MapPosX + (bm->GetRec().x + bm->GetRec().width / 2.0f) * scaleFactor,
      MapPosY + (bm->GetRec().y + bm->GetRec().height / 2.0f) * scaleFactor,
      30 * scaleFactor,
      BLACK
    ); 
  }
  
  if (const Region* fm =GetFavorMarker())
  {
    DrawCircle(
      MapPosX + (fm->GetRec().x + fm->GetRec().width / 2.0f) * scaleFactor,
      MapPosY + (fm->GetRec().y + fm->GetRec().height / 2.0f) * scaleFactor,
      30 * scaleFactor,
      WHITE
    ); 
  }
  
  for (auto& r : m_Regions)
  {
    if(r.GetRuler().has_value())
    {
      DrawCircle(
        MapPosX + (r.GetRec().x + r.GetRec().width / 2.0f) * scaleFactor,
        MapPosY + (r.GetRec().y + r.GetRec().height / 2.0f) * scaleFactor,
        30 * scaleFactor,
        r.GetRuler().value().color
      );
    }
  }
  
  if (state == State::PLACING_BATTLE_MARKER ||
      state == State::PLACING_FAVOR_MARKER)
  {
    const float fontSize = 80.0f;
    std::string text;
    if (state == State::PLACING_BATTLE_MARKER)
    {
      auto chooser = m_Players->at(*m_Turn);
      text = chooser.GetName() + " places battle marker";
    }
    else
    {
      auto chooser = m_Players->at(*m_FavorMarkerChooserIndex);
      text = chooser.GetName() + " places favor marker";
    }

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

std::vector<PlayerInfo> Map::FindWinners() const
{
  // TEST: this method is NOT tested (at all)
  bool allConquered = true;
  std::unordered_map<PlayerInfo, std::vector<size_t>> regionIndices;
  for (size_t i = 0; i < m_Regions.size(); i++)
  {
    auto ruler = m_Regions[i].GetRuler();
    allConquered = allConquered && ruler.has_value();
    if (ruler.has_value())
    {
      regionIndices[ruler.value()].push_back(i);
    }
  }

  if (allConquered)
  {
    size_t max = 0;
    std::vector<PlayerInfo> winners;
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

  return std::vector<PlayerInfo>();
}

bool Map::AreNeighbors(size_t i, size_t j) const
{
  return m_Adjacency[m_Regions.size() * i + j];
}

bool Map::AreNeighbors(size_t i, size_t j, size_t k) const
{
  return AreNeighbors(i, j) && AreNeighbors(i, k) && AreNeighbors(j, k);
}

const Region* Map::GetBattleMarker() const
{
  if (m_BattleMarkerIndex < 0)
  {
    return nullptr;
  }

  return &m_Regions[m_BattleMarkerIndex];
}

Region* Map::GetBattleMarker()
{
  if (m_BattleMarkerIndex < 0)
  {
    return nullptr;
  }

  return &m_Regions[m_BattleMarkerIndex];
}

const Region* Map::GetFavorMarker() const
{
  if (m_FavorMarkerIndex < 0)
  {
    return nullptr;
  }

  return &m_Regions[m_FavorMarkerIndex];
}

Region* Map::GetFavorMarker()
{
  if (m_FavorMarkerIndex < 0)
  {
    return nullptr;
  }

  return &m_Regions[m_FavorMarkerIndex];
}

void Map::ResetBattleMarker()
{
  m_BattleMarkerIndex = -1;
}

void Map::Serialize(StreamWriter& w, const Map& map)
{
  w.WriteVector(map.m_Regions, false);
  w.WriteRaw(map.m_BattleMarkerIndex);
  w.WriteRaw(map.m_FavorMarkerIndex);
}

void Map::Deserialize(StreamReader& r, Map& map)
{
  r.ReadVectorInPlace(map.m_Regions);
  r.ReadRaw(map.m_BattleMarkerIndex);
  r.ReadRaw(map.m_FavorMarkerIndex);
}
