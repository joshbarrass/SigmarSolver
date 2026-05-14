#include <cstdlib>
#include "sigmarsolver.h"
#include "puzzle.h"

extern "C" {

  void *sigmarsgarden_init() {
    SigmarsGarden *sg = new SigmarsGarden();
    return (void*)sg;
  }

  void sigmarsgarden_free(void *p) {
    delete (const SigmarsGarden*)p;
  }

  void sigmarsgarden_setTile(void *p, const int a, const int b,
                             const TileType type) {
    SigmarsGarden *sg = (SigmarsGarden *)p;
    sg->setTile(a, b, type);
  }

  SigmarSolution *sigmarsgarden_solve(const void *p) {
    const SigmarsGarden *sg = (const SigmarsGarden *)p;
    const Solution sol = sg->solve();
    if (!sol.first) return NULL;

    auto moves = sol.second;
    const unsigned int n_moves = moves.size();
    const std::size_t struct_size = sizeof(SigmarSolution) + n_moves*sizeof(SigmarMove);

    SigmarSolution *to_return = (SigmarSolution*)std::malloc(struct_size);
    to_return->n_moves = n_moves;

    for (std::size_t i = 0; i < n_moves; ++i) {
      to_return->moves[i].a1 = moves[i].first.first.a;
      to_return->moves[i].b1 = moves[i].first.first.b;
      to_return->moves[i].t1 = moves[i].first.second.type;
      to_return->moves[i].a2 = moves[i].second.first.a;
      to_return->moves[i].b2 = moves[i].second.first.b;
      to_return->moves[i].t2 = moves[i].second.second.type;
    }

    return to_return;
  }

  void sigmarsolution_free(SigmarSolution *sol) {
    std::free(sol);
  }

  const char *sigmarsgarden_getTypeName(const TileType t) {
    // get_type_name returns a std::string by reference, not by value,
    // so it should be a reference (a pointer for all intents and
    // purposes) to a statically-allocated string. Returning the c_str
    // should be safe.
    return get_type_name(t).c_str();
  }
}
