#pragma once

#include <raylib.h>

struct AssetManager
{
  AssetManager();
  ~AssetManager();

  Texture2D Map;

  Texture2D Mercenary01;
  Texture2D Mercenary02;
  Texture2D Mercenary03;
  Texture2D Mercenary04;
  Texture2D Mercenary05;
  Texture2D Mercenary06;
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
