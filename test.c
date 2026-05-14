#include <stddef.h>
#include <stdio.h>
#include "sigmarsolver.h"

int main() {
  void *sg = sigmarsgarden_init();

  // https://bits.ondrovo.com/sigmar/?seed=1774706658890
  sigmarsgarden_setTile(sg, 0, 0, TILE_GOLD);
  sigmarsgarden_setTile(sg, 1, 0, TILE_WATER);
  sigmarsgarden_setTile(sg, 2, 0, TILE_DEATH);
  sigmarsgarden_setTile(sg, 3, 0, TILE_QUICKSILVER);
  sigmarsgarden_setTile(sg, -1, 0, TILE_AIR);
  sigmarsgarden_setTile(sg, -2, 0, TILE_WATER);
  sigmarsgarden_setTile(sg, -3, 0, TILE_SALT);
  sigmarsgarden_setTile(sg, 0, 1, TILE_WATER);
  sigmarsgarden_setTile(sg, 1, 1, TILE_WATER);
  sigmarsgarden_setTile(sg, 2, 1, TILE_LIFE);
  sigmarsgarden_setTile(sg, -1, 1, TILE_WATER);
  sigmarsgarden_setTile(sg, -2, 1, TILE_LIFE);
  sigmarsgarden_setTile(sg, -3, 1, TILE_WATER);
  sigmarsgarden_setTile(sg, -4, 1, TILE_FIRE);
  sigmarsgarden_setTile(sg, 0, 2, TILE_AIR);
  sigmarsgarden_setTile(sg, 1, 2, TILE_FIRE);
  sigmarsgarden_setTile(sg, 2, 2, TILE_EARTH);
  sigmarsgarden_setTile(sg, -1, 2, TILE_AIR);
  sigmarsgarden_setTile(sg, -2, 2, TILE_DEATH);
  sigmarsgarden_setTile(sg, -3, 2, TILE_SILVER);
  sigmarsgarden_setTile(sg, -4, 2, TILE_FIRE);
  sigmarsgarden_setTile(sg, -5, 2, TILE_EARTH);
  sigmarsgarden_setTile(sg, 0, 3, TILE_AIR);
  sigmarsgarden_setTile(sg, 1, 3, TILE_EARTH);
  sigmarsgarden_setTile(sg, 2, 3, TILE_FIRE);
  sigmarsgarden_setTile(sg, -1, 3, TILE_QUICKSILVER);
  sigmarsgarden_setTile(sg, -2, 3, TILE_AIR);
  sigmarsgarden_setTile(sg, -3, 3, TILE_SALT);
  sigmarsgarden_setTile(sg, -3, 4, TILE_SALT);
  sigmarsgarden_setTile(sg, -2, 4, TILE_EARTH);
  sigmarsgarden_setTile(sg, -3, 5, TILE_EARTH);
  sigmarsgarden_setTile(sg, 0, -1, TILE_FIRE);
  sigmarsgarden_setTile(sg, 1, -1, TILE_COPPER);
  sigmarsgarden_setTile(sg, 2, -1, TILE_EARTH);
  sigmarsgarden_setTile(sg, 3, -1, TILE_IRON);
  sigmarsgarden_setTile(sg, 4, -1, TILE_DEATH);
  sigmarsgarden_setTile(sg, -1, -1, TILE_QUICKSILVER);
  sigmarsgarden_setTile(sg, -2, -1, TILE_QUICKSILVER);
  sigmarsgarden_setTile(sg, 0, -2, TILE_TIN);
  sigmarsgarden_setTile(sg, 1, -2, TILE_LIFE);
  sigmarsgarden_setTile(sg, 2, -2, TILE_EARTH);
  sigmarsgarden_setTile(sg, 3, -2, TILE_WATER);
  sigmarsgarden_setTile(sg, 4, -2, TILE_LIFE);
  sigmarsgarden_setTile(sg, 5, -2, TILE_FIRE);
  sigmarsgarden_setTile(sg, -1, -2, TILE_DEATH);
  sigmarsgarden_setTile(sg, -2, -2, TILE_EARTH);
  sigmarsgarden_setTile(sg, 0, -3, TILE_SALT);
  sigmarsgarden_setTile(sg, -1, -3, TILE_QUICKSILVER);
  sigmarsgarden_setTile(sg, -2, -3, TILE_FIRE);
  sigmarsgarden_setTile(sg, 1, -3, TILE_WATER);
  sigmarsgarden_setTile(sg, 2, -3, TILE_AIR);
  sigmarsgarden_setTile(sg, 3, -3, TILE_LEAD);
  sigmarsgarden_setTile(sg, 3, -4, TILE_AIR);
  sigmarsgarden_setTile(sg, 2, -4, TILE_AIR);
  sigmarsgarden_setTile(sg, 3, -5, TILE_FIRE);

  const SigmarSolution *sol = sigmarsgarden_solve(sg);

  for (size_t i = 0; i < sol->n_moves; ++i) {
    const SigmarMove *m = &sol->moves[i];
    printf("  %zu) [(%d, %d) %s] <-> [(%d, %d) %s]\n", i+1, m->a1, m->b1, sigmarsgarden_getTypeName(m->t1), m->a2, m->b2, sigmarsgarden_getTypeName(m->t2));
  }

  sigmarsolution_free((SigmarSolution*)sol);
  sigmarsgarden_free(sg);

  return 0;
}
