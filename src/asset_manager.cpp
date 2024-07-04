#include <raylib.h>

#include <asset_manager.hpp>

void AssetManager::Load()
{
  Map = LoadTexture("assets/map.png");

  Bishop = LoadTexture("assets/bishop.png");
  Drummer = LoadTexture("assets/drummer.png");
  Heroine = LoadTexture("assets/heroine.png");
  Scarecrow = LoadTexture("assets/scarecrow.png");
  Spring = LoadTexture("assets/spring.png");
  Spy = LoadTexture("assets/spy.png");
  Turncoat = LoadTexture("assets/turncoat.png");
  Winter = LoadTexture("assets/winter.png");
}

AssetManager::~AssetManager()
{
  // NOTE: reverse ordering recommended

  UnloadTexture(Winter);
  UnloadTexture(Turncoat);
  UnloadTexture(Spy);
  UnloadTexture(Spring);
  UnloadTexture(Scarecrow);
  UnloadTexture(Heroine);
  UnloadTexture(Drummer);
  UnloadTexture(Bishop);

  UnloadTexture(Map);
}
