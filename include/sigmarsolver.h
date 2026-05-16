#ifndef SIGMARSOLVER_H
#define SIGMARSOLVER_H
#include "dllexport.h"
#ifdef __cplusplus
extern "C" {
#endif

enum TileType {
  TILE_NONE = 0,
  TILE_SALT,
  TILE_AIR,
  TILE_FIRE,
  TILE_WATER,
  TILE_EARTH,
  TILE_LIFE,
  TILE_DEATH,
  TILE_QUICKSILVER,
  TILE_LEAD,
  TILE_TIN,
  TILE_IRON,
  TILE_COPPER,
  TILE_SILVER,
  TILE_GOLD
};
#ifndef __cplusplus
typedef enum TileType TileType;
#endif
#ifndef SIGMAR_TYPE_ENUM_ONLY

typedef struct {
  int a1;
  int b1;
  TileType t1;
  int a2;
  int b2;
  TileType t2;
} SigmarMove;

typedef struct {
  unsigned int n_moves;
  SigmarMove moves[];
} SigmarSolution;

  // Allocates and returns a pointer to an opaque solver instance. The
  // caller is responsible for freeing it with sigmarsgarden_free.
  EXPORT void *sigmarsgarden_init();

  // Frees a solver created by sigmarsgarden_init.
  EXPORT void sigmarsgarden_free(void*);

  // Sets a single tile in a solver instance.
  EXPORT void sigmarsgarden_setTile(void *p, const int a, const int b, const TileType type);

  // Solves the puzzle. Returns a SigmarSolution allocated on the
  // heap. The caller is responsible for freeing it with
  // sigmarsolution_free. If the puzzle cannot be solved, returns
  // NULL.
  EXPORT SigmarSolution *sigmarsgarden_solve(const void*);

  // Frees a SigmarSolution created by sigmarsgarden_solve.
  EXPORT void sigmarsolution_free(SigmarSolution*);

  // Returns the human-readable tile type name for a given
  // TileType. If the TileType is unrecognised, returns "UNKNOWN". All
  // strings are statically-allocated and shared, and should never be
  // modified.
  EXPORT const char *sigmarsgarden_getTypeName(const TileType t);

#endif
#ifdef __cplusplus
}
#endif
#endif
