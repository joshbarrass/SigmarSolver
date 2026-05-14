#ifndef SIGMARSOLVER_H
#define SIGMARSOLVER_H
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

  void *sigmarsgarden_init();
  void sigmarsgarden_free(void*);

  void sigmarsgarden_setTile(void *p, const int a, const int b, const unsigned int type);

  void sigmarsolution_free(SigmarSolution*);
  SigmarSolution *sigmarsgarden_solve(const void*);

  const char *sigmarsgarden_getTypeName(const TileType t);

#endif
#ifdef __cplusplus
}
#endif
#endif
