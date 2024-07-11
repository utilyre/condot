#include <raylib.h>

#include <asset_manager.hpp>

AssetManager::AssetManager()
{
  int width = GetScreenWidth();
  int height = GetScreenHeight();

  Image background = LoadImage("assets/background.png");
  if ((float)background.height / background.width > (float)height / width)
    ImageResize(&background, width, ((float)width / background.width) * background.height);
  else
    ImageResize(&background, ((float)height / background.height) * background.width, height);
  Background = LoadTextureFromImage(background);
  UnloadImage(background);

  Image map = LoadImage("assets/map.png");
  ImageResize(&map, 0.81f * map.width, 0.81f * map.height);
  Map = LoadTextureFromImage(map);
  UnloadImage(map);

  Mercenary1 = LoadTexture("assets/mercenary/1.png");
  Mercenary2 = LoadTexture("assets/mercenary/2.png");
  Mercenary3 = LoadTexture("assets/mercenary/3.png");
  Mercenary4 = LoadTexture("assets/mercenary/4.png");
  Mercenary5 = LoadTexture("assets/mercenary/5.png");
  Mercenary6 = LoadTexture("assets/mercenary/6.png");
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
  UnloadTexture(Mercenary6);
  UnloadTexture(Mercenary5);
  UnloadTexture(Mercenary4);
  UnloadTexture(Mercenary3);
  UnloadTexture(Mercenary2);
  UnloadTexture(Mercenary1);

  UnloadTexture(Map);
  UnloadTexture(Background);
}
