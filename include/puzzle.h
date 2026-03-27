#ifndef PUZZLE_H
#define PUZZLE_H

#include <unordered_map>
#include "tile.h"

class SigmarsGarden {
public:
  SigmarsGarden(){}
  SigmarsGarden(const SigmarsGarden &sg);
  ~SigmarsGarden();

  Tile getTileAt(const Coord &c) const;
  void setTile(const Coord &c, const Tile &t);

private:
  std::unordered_map<Coord, Tile> tiles;
};

#endif
