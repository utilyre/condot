#pragma once

struct Card
{
  enum Type {
    MERCENARY,
    BISHOP,
    DRUMMER,
    HEROINE,
    SCARECROW,
    SPRING,
    SPY,
    TURNCOAT,
    WINTER,
  } type;
  int power; // used only for mercenary type
};
