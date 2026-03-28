#ifndef TILE_TYPE_H
#define TILE_TYPE_H

#include <ostream>

enum TileType {
  TILE_NONE,
  TILE_SALT,
  TILE_AIR,
  TILE_FIRE,
  TILE_WATER,
  TILE_EARTH,
  TILE_QUICKSILVER,
  TILE_LEAD,
  TILE_TIN,
  TILE_IRON,
  TILE_COPPER,
  TILE_SILVER,
  TILE_GOLD
};

std::ostream &operator<<(std::ostream &os, TileType &t);
std::ostream &operator<<(std::ostream &os, const TileType &t);

#endif
