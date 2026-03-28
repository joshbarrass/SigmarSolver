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
  TILE_LIFE,
  TILE_DEATH,
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

bool is_metal(const TileType t);
TileType get_prev_metal(const TileType t);
TileType get_next_metal(const TileType t);
bool types_can_match(const TileType t1, const TileType t2);
bool operator+(const TileType t1, const TileType t2);

#endif
