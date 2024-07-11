#pragma once

#include <raylib.h>

struct AssetManager
{
  AssetManager();
  ~AssetManager();

  Texture2D Background;
  Texture2D Map;

  Texture2D Mercenary1;
  Texture2D Mercenary2;
  Texture2D Mercenary3;
  Texture2D Mercenary4;
  Texture2D Mercenary5;
  Texture2D Mercenary6;
  Texture2D Mercenary10;

  Texture2D Bishop; // Rish Sefid
  Texture2D Drummer; // Tabl Zan
  Texture2D Heroine; // Shah Dokht
  Texture2D Scarecrow; // Matarsak
  Texture2D Spring; // Bahar
  Texture2D Spy; // Shirzan
  Texture2D Turncoat; // Parchamdar
  Texture2D Winter; // Zemestan
};
