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
