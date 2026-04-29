#ifndef TILE_H
#define TILE_H

#include <unordered_map>
#include <cstddef>
#include "tile_type.h"

// Hexagonal coordinates
/*

          _ b
     /\   /|
    /  \ /
   /    \
  |      |
  |      | ----> a
  |      |
   \    /
    \  /
     \/

Each tile uniquely defined by (a,b)
Neighbours are (a+1,b) (a-1,b) (a,b+1) (a,b-1) (a+1,b-1) (a-1,b+1)
*/

struct Coord {
  Coord(int A, int B) : a(A), b(B) {}
  bool operator==(const Coord & c) const { return a == c.a && b == c.b; }
  int a;
  int b;
};

template<>
struct std::hash<Coord>
{
    std::size_t operator()(const Coord& c) const noexcept
    {
        std::size_t h1 = std::hash<int>{}(c.a);
        std::size_t h2 = std::hash<int>{}(c.b);
        return h1 ^ (h2 << 1); // or use boost::hash_combine
    }
};

struct Tile {
  Tile() : type(TILE_NONE), removed(true) {}
  Tile(TileType t) : type(t), removed(false) {}
  Tile(TileType t, bool rem) : type(t), removed(rem) {}
  ~Tile() {}
  TileType type;
  bool removed;
};

#endif
