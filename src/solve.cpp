#include "puzzle.h"

bool SigmarsGarden::is_solved() const {
  for (const auto iter : tiles) {
    if (!iter.second.removed) {
      return false;
    }
  }
  return true;
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
