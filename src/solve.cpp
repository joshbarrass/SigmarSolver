#include "puzzle.h"
#include <iostream>
#include <random>
#include <chrono>

std::default_random_engine rng;

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
  bool solved;
  std::stack<Move> movestack_final;
  for (int trials = 0; trials < 30; ++trials) {
    std::cout << "Trial" << trials+1 << std::endl;
    // seed the RNG
    // CC BY-SA https://stackoverflow.com/a/42637679
    rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
    // make a mutable copy
    SigmarsGarden sg = SigmarsGarden(this);
    sg.moves_tried = 0;

    std::stack<Move> movestack;
    solved = sg.solver_internal(movestack);
    if (solved) {
      movestack_final = movestack;
      std::cout << "Finished in " << sg.moves_tried << " moves" << std::endl;
      break;
    }
  }

  // unwind the stack if solved
  std::vector<Move> moves;
  if (solved) {
    while (movestack_final.size() > 0) {
      moves.insert(moves.begin(), movestack_final.top());
      movestack_final.pop();
    }
  }

  std::pair<bool, std::vector<Move>> output(solved, moves);
  return output;
}

bool SigmarsGarden::solver_internal(std::stack<Move> &movestack) {
  if (moves_tried >= 100000) return false;
  ++moves_tried;
  if (is_solved()) return true;
  // if (!is_solveable()) return false;
  const auto moves = getAllPossibleMoves();
  std::size_t size = moves.size();
  std::uniform_int_distribution<int> distribution(0,size-1);
  std::size_t start_index = distribution(rng);
  for (std::size_t i = 0; i < size; ++i) {
    const Move move = moves[(start_index+i)%size];
    doMove(move);
    movestack.push(move);
    bool solved = solver_internal(movestack);
    if (solved) return true;
    movestack.pop();
    undoMove(move);
  }
  return false;
}
