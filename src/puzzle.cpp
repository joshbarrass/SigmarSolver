#include <cstdint>
#include "puzzle.h"

SigmarsGarden::SigmarsGarden(const SigmarsGarden &sg) {
  for (const auto &entry : sg.tiles) {
    tiles[entry.first] = entry.second;
  }
}

SigmarsGarden::~SigmarsGarden() {}

Tile SigmarsGarden::getTileAt(const Coord &c) const {
  const auto val = tiles.find(c);
  if (val != tiles.end()) return val->second;
  return Tile();
}

void SigmarsGarden::setTile(const Coord &c, const Tile &t) {
  tiles[c] = t;
}

// Returns a coord representing the ith adjacent cell. i=0 corresponds
// to theta=0 in polar coordinates, i.e. the cell to the right. i then
// moves around the adjacent cells counter-clockwise. i < 0 and i >= 6
// are valid and use modular arithmetic.
Coord get_adjacent_coord(const Coord &c, const int i) {
  switch (i % 6) {
  case 0:
    return Coord(c.a+1, c.b);
  case 1:
    return Coord(c.a, c.b+1);
  case 2:
    return Coord(c.a-1, c.b+1);
  case 3:
    return Coord(c.a-1, c.b);
  case 4:
    return Coord(c.a, c.b-1);
  case 5:
    break;
  }
  return Coord(c.a+1, c.b-1);
}

bool SigmarsGarden::canMoveTile(const Coord &c) const {
  const Tile t = getTileAt(c);
  if (t.type == TILE_NONE) return false;

  // count number of contiguous free spaces
  // start by making a linear map of free spaces
  bool freemap[6] = { false };
  for (size_t i = 0; i < 6; ++i) {
    const Tile t_ = getTileAt(get_adjacent_coord(c, i));
    freemap[i] = t_.removed || t_.type == TILE_NONE;
  }
  // loop twice around the map, counting the maximum number of free
  // spaces we see. looping around avoids edge effects. If at any
  // point we see 3 in a row, break out early.
  int contiguous_free = 0;
  for (size_t i = 0; i < 12; ++i) {
    if (freemap[i%6]) ++contiguous_free;
    else contiguous_free = 0;
    if (contiguous_free >= 3) return true;
  }

  return false;
}
