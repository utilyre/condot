#include <raylib.h>

#include <asset_manager.hpp>

AssetManager::AssetManager()
{
  Image map = LoadImage("assets/map.png");
  ImageResize(&map, 0.81f * map.width, 0.81f * map.height);
  Map = LoadTextureFromImage(map);
  UnloadImage(map);

  Mercenary01 = LoadTexture("assets/mercenary/01.png");
  Mercenary02 = LoadTexture("assets/mercenary/02.png");
  Mercenary03 = LoadTexture("assets/mercenary/03.png");
  Mercenary04 = LoadTexture("assets/mercenary/04.png");
  Mercenary05 = LoadTexture("assets/mercenary/05.png");
  Mercenary06 = LoadTexture("assets/mercenary/06.png");
  Mercenary10 = LoadTexture("assets/mercenary/10.png");

  Bishop = LoadTexture("assets/special/bishop.png");
  Drummer = LoadTexture("assets/special/drummer.png");
  Heroine = LoadTexture("assets/special/heroine.png");
  Scarecrow = LoadTexture("assets/special/scarecrow.png");
  Spring = LoadTexture("assets/special/spring.png");
  Spy = LoadTexture("assets/special/spy.png");
  Turncoat = LoadTexture("assets/special/turncoat.png");
  Winter = LoadTexture("assets/special/winter.png");
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

  UnloadTexture(Mercenary10);
  UnloadTexture(Mercenary06);
  UnloadTexture(Mercenary05);
  UnloadTexture(Mercenary04);
  UnloadTexture(Mercenary03);
  UnloadTexture(Mercenary02);
  UnloadTexture(Mercenary01);

  UnloadTexture(Map);
}
