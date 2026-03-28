#include "puzzle.h"
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
  return 0;
}
