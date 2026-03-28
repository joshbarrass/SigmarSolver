#include "puzzle.h"
#include "tile_type.h"
#include <iostream>

int main() {
  SigmarsGarden sg = SigmarsGarden();
  Tile t = sg.getTileAt(Coord(0, 0));
  std::cout << "Tile: " << t.type << " " << t.removed << std::endl;

  sg.setTile(Coord(0, 0), Tile(TILE_GOLD));
  sg.setTile(Coord(1, 0), Tile(TILE_GOLD));
  sg.setTile(Coord(-1, 0), Tile(TILE_GOLD));
  t = sg.getTileAt(Coord(0, 0));
  std::cout << "Tile: " << t.type << " " << t.removed << std::endl;
  std::cout << "Can move? " << sg.canMoveTile(Coord(0,0)) << std::endl;

  std::cout << TILE_GOLD << " is metal? " << is_metal(TILE_GOLD) << std::endl;
  std::cout << TILE_WATER << " is metal? " << is_metal(TILE_WATER) << std::endl;
  return 0;
}
