#include <raylib.h>

#include <asset_manager.hpp>

AssetManager::AssetManager()
{
  Image map = LoadImage("assets/map.png");
  ImageResize(&map, 0.81f * map.width, 0.81f * map.height);
  Map = LoadTextureFromImage(map);
  UnloadImage(map);

  Back = LoadTexture("assets/cards/back.png");
  Mercenary1 = LoadTexture("assets/cards/1.png");
  Mercenary2 = LoadTexture("assets/cards/2.png");
  Mercenary3 = LoadTexture("assets/cards/3.png");
  Mercenary4 = LoadTexture("assets/cards/4.png");
  Mercenary5 = LoadTexture("assets/cards/5.png");
  Mercenary6 = LoadTexture("assets/cards/6.png");
  Mercenary10 = LoadTexture("assets/cards/10.png");
  Bishop = LoadTexture("assets/cards/bishop.png");
  Drummer = LoadTexture("assets/cards/drummer.png");
  Heroine = LoadTexture("assets/cards/heroine.png");
  Scarecrow = LoadTexture("assets/cards/scarecrow.png");
  Spring = LoadTexture("assets/cards/spring.png");
  Spy = LoadTexture("assets/cards/spy.png");
  Turncoat = LoadTexture("assets/cards/turncoat.png");
  Winter = LoadTexture("assets/cards/winter.png");
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
  UnloadTexture(Mercenary6);
  UnloadTexture(Mercenary5);
  UnloadTexture(Mercenary4);
  UnloadTexture(Mercenary3);
  UnloadTexture(Mercenary2);
  UnloadTexture(Mercenary1);
  UnloadTexture(Back);

  UnloadTexture(Map);
}
