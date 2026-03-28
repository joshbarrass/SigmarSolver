#ifndef PUZZLE_H
#define PUZZLE_H

#include <unordered_map>
#include <utility>
#include <vector>
#include "tile.h"

class SigmarsGarden {
public:
  SigmarsGarden(){}
  SigmarsGarden(const SigmarsGarden &sg);
  ~SigmarsGarden();

  Tile getTileAt(const Coord &c) const;
  void setTile(const Coord &c, const Tile &t);
  bool canMoveTile(const Coord &c) const;
  std::vector<std::pair<Coord, Tile>> getMoveableTiles() const;

private:
  std::unordered_map<Coord, Tile> tiles;
};

#endif
