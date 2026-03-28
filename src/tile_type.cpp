#include "tile_type.h"
#include <unordered_map>
#include <unordered_set>
#include <string>

const std::unordered_map<TileType, std::string> tile_type_names{
    {TILE_NONE, "NONE"},
    {TILE_SALT, "SALT"},
    {TILE_AIR, "AIR"},
    {TILE_FIRE, "FIRE"},
    {TILE_WATER, "WATER"},
    {TILE_EARTH, "EARTH"},
    {TILE_QUICKSILVER, "QUICKSILVER"},
    {TILE_LEAD, "LEAD"},
    {TILE_TIN, "TIN"},
    {TILE_IRON, "IRON"},
    {TILE_COPPER, "COPPER"},
    {TILE_SILVER, "SILVER"},
    {TILE_GOLD, "GOLD"}
};

const std::unordered_set<TileType> metal_tiles {TILE_LEAD, TILE_TIN, TILE_IRON, TILE_COPPER, TILE_SILVER, TILE_GOLD};

std::ostream &operator<<(std::ostream &os, TileType &t) {
  return operator<<(os, const_cast<const TileType &>(t));
}

std::ostream &operator<<(std::ostream &os, const TileType &t) {
  const auto &s = tile_type_names.find(t);
  if (s == tile_type_names.end()) {
    os << "UNKNOWN?(" << static_cast<int>(t) << ")";
  } else {
    os << s->second;
  }
  return os;
}

bool is_metal(const TileType t) {
  return metal_tiles.count(t) == 1;
}
