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
  Tile getTileAt(const int a, const int b) const;

  void setTile(const Coord &c, const Tile &t);
  void setTile(const int a, const int b, const Tile &t);
  void setTile(const Coord &c, const TileType t);
  void setTile(const int a, const int b, const TileType t);

  bool canMoveTile(const Coord &c) const;
  bool canMoveTile(const int a, const int b) const;

  std::vector<std::pair<Coord, Tile>> getMoveableTiles() const;

private:
  std::unordered_map<Coord, Tile> tiles;
};

#endif
