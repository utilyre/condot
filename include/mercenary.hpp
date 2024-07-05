#include <raylib.h>

#include <asset_manager.hpp>
#include <card.hpp>

class Mercenary : public Card
{
public:
  Mercenary(int power);

  Texture2D GetAsset(const AssetManager& assets) const override;
  int GetPower() const;

private:
  int m_Power;
};
