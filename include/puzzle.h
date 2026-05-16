#ifndef PUZZLE_H
#define PUZZLE_H

#include <unordered_map>
#include <utility>
#include <vector>
#include <stack>
#include <cstddef>
#include <cstdint>
#include "tile.h"
#include "dllexport.h"

typedef std::pair<Coord, Tile> PlacedTile;
typedef std::pair<PlacedTile, PlacedTile> Move;
typedef std::pair<bool, std::vector<Move>> Solution;

class EXPORT SigmarsGarden {
public:
  SigmarsGarden(){}
  SigmarsGarden(const SigmarsGarden &sg);
  SigmarsGarden(const SigmarsGarden *sg);
  SigmarsGarden(const void *buf);
  ~SigmarsGarden();

  Tile getTileAt(const Coord &c) const;
  Tile getTileAt(const int a, const int b) const;

  void setTile(const Coord &c, const Tile &t);
  void setTile(const int a, const int b, const Tile &t);
  void setTile(const Coord &c, const TileType t);
  void setTile(const int a, const int b, const TileType t);

  bool canMoveTile(const Coord &c) const;
  bool canMoveTile(const int a, const int b) const;

  std::vector<PlacedTile> getMoveableTiles() const;
  std::vector<Move> getAllPossibleMoves() const;

  void doMove(const Move m);
  void undoMove(const Move m);

  bool is_solved() const;
  bool is_solveable() const;

  Solution solve() const;

  std::size_t serialise(const std::size_t bufsize, void *buf) const;
  std::size_t serialise_required_buf_size() const;

private:
  bool solver_internal(std::stack<Move>&);

  std::unordered_map<Coord, Tile> tiles;
  std::uint64_t moves_tried;
};

#endif
