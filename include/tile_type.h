#ifndef TILE_TYPE_H
#define TILE_TYPE_H

#include <ostream>
#include <string>
#include "dllexport.h"
#define SIGMAR_TYPE_ENUM_ONLY
#include "sigmarsolver.h"

EXPORT std::ostream &operator<<(std::ostream &os, TileType &t);
EXPORT std::ostream &operator<<(std::ostream &os, const TileType &t);

bool is_metal(const TileType t);
TileType get_prev_metal(const TileType t);
TileType get_next_metal(const TileType t);
bool types_can_match(const TileType t1, const TileType t2);
bool operator+(const TileType t1, const TileType t2);
EXPORT const std::string &get_type_name(const TileType t);

#endif
