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

// I'm defining these really explicitly. Long, but robust.

TileType get_prev_metal(const TileType t) {
  switch (t) {
  case TILE_TIN: return TILE_NONE;
  case TILE_IRON: return TILE_TIN;
  case TILE_COPPER: return TILE_IRON;
  case TILE_SILVER: return TILE_COPPER;
  case TILE_GOLD: return TILE_SILVER;
  default:
    break;
  }
  return TILE_NONE;
}

TileType get_next_metal(const TileType t) {
  switch (t) {
  case TILE_TIN: return TILE_IRON;
  case TILE_IRON: return TILE_COPPER;
  case TILE_COPPER: return TILE_SILVER;
  case TILE_SILVER: return TILE_GOLD;
  case TILE_GOLD: return TILE_NONE;
  default:
    break;
  }
  return TILE_NONE;
}

bool types_can_match(const TileType t1, const TileType t2) {
  // metal - quicksilver
  if (is_metal(t1)) {
    return t2 == TILE_QUICKSILVER;
  }
  if (is_metal(t2)) {
    return t1 == TILE_QUICKSILVER;
  }

  // if we reach here, neither is metal. Must be basic element, salt,
  // or quicksilver.
  // quicksilver only matches with metals
  if (t1 == TILE_QUICKSILVER || t2 == TILE_QUICKSILVER) {
    return false;
  }

  // otherwise, match valid if they're the same or if one of them is
  // salt
  return t1 == t2 || t1 == TILE_SALT || t2 == TILE_SALT;
}

bool operator+(const TileType t1, const TileType t2) {
  return types_can_match(t1, t2);
}
