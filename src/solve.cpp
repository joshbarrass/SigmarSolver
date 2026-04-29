#include "puzzle.h"
#include <iostream>

bool SigmarsGarden::is_solved() const {
  for (const auto iter : tiles) {
    if (!iter.second.removed) {
      return false;
    }
  }
  return true;
}
 
// TODO: optimise this to use information stored in the struct, rather
// than recalculating O(N) every call
bool SigmarsGarden::is_solveable() const {
  std::unordered_map<TileType, int> tile_counts;
  tile_counts[TILE_SALT] = 0;
  for (const auto iter : tiles) {
    if (TILE_SALT + iter.second.type)
      ++tile_counts[iter.second.type];
  }

  int salts = tile_counts[TILE_SALT];
  tile_counts.erase(TILE_SALT);
  int salts_required = 0;
  for (const auto iter : tile_counts) {
    salts_required += iter.second % 2;
  }

  return salts >= salts_required;
}

Solution SigmarsGarden::solve() const {
  // make a mutable copy
  SigmarsGarden sg = SigmarsGarden(this);

  std::vector<Move> moves;
  std::stack<Move> movestack;
  const bool solved = sg.solver_internal(movestack);

  // unwind the stack if solved
  if (solved) {
    while (movestack.size() > 0) {
      moves.insert(moves.begin(), movestack.top());
      movestack.pop();
    }
  }

  std::pair<bool, std::vector<Move>> output(solved, moves);
  return output;
}

bool SigmarsGarden::solver_internal(std::stack<Move> &movestack) {
  if (is_solved()) return true;
  // if (!is_solveable()) return false;
  const auto moves = getAllPossibleMoves();
  for (const auto move : moves) {
    doMove(move);
    movestack.push(move);
    bool solved = solver_internal(movestack);
    if (solved) return true;
    movestack.pop();
    undoMove(move);
  }
  return false;
}
