#pragma once

#include <string>

#include <player.hpp>

class Region {
public:
  explicit Region(const std::string& name);

  void SetRuler(const Player* ruler);
  const Player* GetRuler() const;
  const std::string& GetName() const;

private:
  std::string m_Name;
  const Player* m_Ruler;
};

// const Region REGIONS[14] = {
//   Region("bella"),
//   Region("caline"),
//   Region("enna"),
//   Region("atela"),
//   Region("pladaci"),
//   Region("borge"),
//   Region("dimase"),
//   Region("rollo"),
//   Region("mornia"),
//   Region("olivadi"),
//   Region("talmone"),
//   Region("armento"),
//   Region("lia"),
//   Region("elinia"),
// };

// const bool MAP[14][14] = {
//   /*                 0  1  2  3  4  5  6  7  8  9 10 11 12 13 */
//   /*  0: bella   */ {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//   /*  1: caline  */ {1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
//   /*  2: enna    */ {0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
//   /*  3: altela  */ {0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
//   /*  4: pladaci */ {1, 0, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0},
//   /*  5: borge   */ {0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0},
//   /*  6: dimase  */ {0, 0, 1, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
//   /*  7: rollo   */ {0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1},
//   /*  8: mornia  */ {0, 0, 0, 0, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0},
//   /*  9: olivadi */ {0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0},
//   /* 10: talmone */ {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1},
//   /* 11: armento */ {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0},
//   /* 12: lia     */ {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
//   /* 13: elinia  */ {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0},
// };
