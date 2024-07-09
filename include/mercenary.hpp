#include <raylib.h>

#include <asset_manager.hpp>

class Mercenary
{
public:
  Mercenary(int power);

  Texture2D GetAsset(const AssetManager& assets) const;
  int GetPower() const;

private:
  int m_Power;
};
