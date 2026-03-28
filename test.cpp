#include "puzzle.h"
#include "tile_type.h"
#include <iostream>

int main() {
  SigmarsGarden sg = SigmarsGarden();
  Tile t = sg.getTileAt(Coord(0, 0));
  std::cout << "Tile: " << t.type << " " << t.removed << std::endl;

  sg.setTile(0, 0, TILE_SILVER);
  sg.setTile(1, 0, TILE_GOLD);
  sg.setTile(-1, 0, TILE_GOLD);
  t = sg.getTileAt(0, 0);
  std::cout << "Tile: " << t.type << " " << t.removed << std::endl;
  std::cout << "Can move centre? " << sg.canMoveTile(0,0) << std::endl;
  std::cout << "Can move gold? " << sg.canMoveTile(-1,0) << std::endl;
  sg.setTile(-1, 0, TILE_LEAD);
  std::cout << "Can move lead? " << sg.canMoveTile(-1,0) << std::endl;

  std::cout << TILE_GOLD << " is metal? " << is_metal(TILE_GOLD) << std::endl;
  std::cout << TILE_WATER << " is metal? " << is_metal(TILE_WATER) << std::endl;

  TileType m = TILE_TIN;
  std::cout << "Metal sequence: ";
  for (size_t i = 0; i < 6; ++i) {
    std::cout << m << " ";
    m = get_next_metal(m);
  }
  std::cout << std::endl;
  m = TILE_GOLD;
  std::cout << "Metal sequence: ";
  for (size_t i = 0; i < 6; ++i) {
    std::cout << m << " ";
    m = get_prev_metal(m);
  }
  std::cout << std::endl;

  sg.setTile(2, 0, TILE_QUICKSILVER);
  const auto moveable = sg.getMoveableTiles();
  std::cout << "Moveable tiles:" << std::endl;
  for (const auto tile : moveable) {
    std::cout << "  (" << tile.first.a << "," << tile.first.b << ") " << tile.second.type << std::endl;
  }

  return 0;
}
