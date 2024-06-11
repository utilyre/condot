#include <iostream>

#include <battle.hpp>

Battle::Battle(Turn* turn, const Map* map)
: m_Turn(turn),
  m_Map(map),
  m_Region(nullptr),
  m_Season(Season::None)
{}

void Battle::Start() {
  SelectRegion();
}

void Battle::SelectRegion() {
  const std::vector<Region>& regions = m_Map->GetRegions();

  size_t regionIdx;
  do {
    std::system("clear");

    std::cout << "Choose a region to start the war in:\n";
    for (size_t i = 0; i < regions.size(); i++) {
      std::cout << "  " << i + 1 << ". " << regions[i].GetName() << '\n';
    }

    std::cout << "\n@" << m_Turn->GetCurrentPlayer().GetName()
      << " [1-" << regions.size() << "]: ";

    std::cin >> regionIdx;
  } while (regionIdx == 0 || regionIdx > regions.size());

  m_Region = m_Map->GetRegion(regionIdx - 1);
}
