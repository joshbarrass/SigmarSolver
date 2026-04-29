#include <cstddef>
#include "puzzle.h"

SigmarsGarden::SigmarsGarden(const SigmarsGarden &sg) {
  for (const auto &entry : sg.tiles) {
    tiles[entry.first] = entry.second;
  }
}

SigmarsGarden::SigmarsGarden(const SigmarsGarden *sg) {
  for (const auto &entry : sg->tiles) {
    tiles[entry.first] = entry.second;
  }
}

SigmarsGarden::~SigmarsGarden() {}

Tile SigmarsGarden::getTileAt(const Coord &c) const {
  const auto val = tiles.find(c);
  if (val != tiles.end()) return val->second;
  return Tile();
}

Tile SigmarsGarden::getTileAt(const int a, const int b) const {
  return getTileAt(Coord(a, b));
}

void SigmarsGarden::setTile(const Coord &c, const Tile &t) {
  tiles[c] = t;
}

void SigmarsGarden::setTile(const int a, const int b, const TileType t) {
  setTile(Coord(a, b), Tile(t));
}

void SigmarsGarden::setTile(const Coord &c, const TileType t) {
  setTile(c, Tile(t));
}

void SigmarsGarden::setTile(const int a, const int b, const Tile &t) {
  setTile(Coord(a, b), t);
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
  if (t.removed || t.type == TILE_NONE) return false;

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
    if (contiguous_free >= 3) break;
  }

  if (contiguous_free < 3) return false;

  // walk back through the metal sequence checking to see if it's
  // present in the puzzle
  TileType metal = get_prev_metal(t.type); // will be none if not a metal
  while (metal != TILE_NONE) {
    for (const auto &iter : tiles) {
      // if this metal still exists in the puzzle, we can't remove
      if (iter.second.type == metal && !iter.second.removed) {
        return false;
      }
    }
    metal = get_prev_metal(metal);
  }

  return true;
}

bool SigmarsGarden::canMoveTile(const int a, const int b) const {
  return canMoveTile(Coord(a, b));
}

std::vector<PlacedTile> SigmarsGarden::getMoveableTiles() const {
  std::vector<PlacedTile> moveable;
  for (const auto tile : tiles) {
    const std::pair<Coord, Tile> t = tile;
    if (canMoveTile(t.first)) moveable.push_back(t);
  }
  return moveable;
}

std::vector<Move> SigmarsGarden::getAllPossibleMoves() const {
  std::vector<Move> moves;

  const auto moveable = getMoveableTiles();

  // loop through all pairs of tiles seeing whether they could be
  // matched with each other. If they can, it's a valid move!
  for (size_t i = 0; i < moveable.size(); ++i) {
    // special exception for gold!
    if (moveable[i].second.type == TILE_GOLD) {
      const Move move = Move(moveable[i],
                             PlacedTile(moveable[i].first, Tile(TILE_NONE, false))
                             );
      moves.push_back(move);
      continue;
    }

    for (size_t j = i + 1; j < moveable.size(); ++j) {
      if (moveable[i].second.type + moveable[j].second.type) {
        const Move move = Move(moveable[i], moveable[j]);
        moves.push_back(move);
      }
    }
  }

  return moves;
}

void SigmarsGarden::doMove(const Move m) {
  if (m.first.second.type != TILE_NONE)
    tiles[m.first.first].removed = true;
  if (m.second.second.type != TILE_NONE)
    tiles[m.second.first].removed = true;
}

void SigmarsGarden::undoMove(const Move m) {
  if (m.first.second.type != TILE_NONE)
    tiles[m.first.first].removed = false;
  if (m.second.second.type != TILE_NONE)
    tiles[m.second.first].removed = false;
}
