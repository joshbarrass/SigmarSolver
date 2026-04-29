#include "puzzle.h"
#include "tile_type.h"
#include <iostream>

using namespace std;

int main() {
  SigmarsGarden sg = SigmarsGarden();

  // https://bits.ondrovo.com/sigmar/?seed=1777487412104
  sg.setTile(0, 0, TILE_GOLD);
  sg.setTile(1, 0, TILE_AIR);
  sg.setTile(2, 0, TILE_IRON);
  sg.setTile(3, 0, TILE_DEATH);
  sg.setTile(4, 0, TILE_EARTH);
  sg.setTile(5, 0, TILE_AIR);
  sg.setTile(-1, 0, TILE_SILVER);
  sg.setTile(-2, 0, TILE_FIRE);
  sg.setTile(-4, 0, TILE_SALT);
  sg.setTile(0, 1, TILE_AIR);
  sg.setTile(4, 1, TILE_DEATH);
  sg.setTile(-1, 1, TILE_QUICKSILVER);
  sg.setTile(-3, 1, TILE_WATER);
  sg.setTile(-4, 1, TILE_WATER);
  sg.setTile(0, 2, TILE_LIFE);
  sg.setTile(1, 2, TILE_SALT);
  sg.setTile(2, 2, TILE_EARTH);
  sg.setTile(3, 2, TILE_FIRE);
  sg.setTile(-1, 2, TILE_FIRE);
  sg.setTile(-2, 2, TILE_QUICKSILVER);
  sg.setTile(-4, 2, TILE_WATER);
  sg.setTile(1, 3, TILE_SALT);
  sg.setTile(-3, 3, TILE_DEATH);
  sg.setTile(-5, 3, TILE_SALT);
  sg.setTile(0, 4, TILE_LIFE);
  sg.setTile(-1, 4, TILE_FIRE);
  sg.setTile(-2, 4, TILE_WATER);
  sg.setTile(-3, 4, TILE_TIN);
  sg.setTile(-4, 4, TILE_WATER);
  sg.setTile(-5, 4, TILE_QUICKSILVER);
  sg.setTile(-1, 5, TILE_FIRE);
  sg.setTile(-5, 5, TILE_LEAD);
  sg.setTile(0, -1, TILE_AIR);
  sg.setTile(1, -1, TILE_AIR);
  sg.setTile(2, -1, TILE_LIFE);
  sg.setTile(4, -1, TILE_LIFE);
  sg.setTile(-1, -1, TILE_QUICKSILVER);
  sg.setTile(-3, -1, TILE_EARTH);
  sg.setTile(-4, -1, TILE_WATER);
  sg.setTile(0, -2, TILE_COPPER);
  sg.setTile(2, -2, TILE_DEATH);
  sg.setTile(4, -2, TILE_FIRE);
  sg.setTile(-2, -2, TILE_EARTH);
  sg.setTile(0, -3, TILE_WATER);
  sg.setTile(2, -3, TILE_QUICKSILVER);
  sg.setTile(4, -3, TILE_AIR);
  sg.setTile(-1, -3, TILE_AIR);
  sg.setTile(0, -4, TILE_EARTH);
  sg.setTile(2, -4, TILE_FIRE);
  sg.setTile(3, -4, TILE_FIRE);
  sg.setTile(4, -4, TILE_AIR);
  sg.setTile(5, -4, TILE_WATER);
  sg.setTile(0, -5, TILE_EARTH);
  sg.setTile(1, -5, TILE_EARTH);
  sg.setTile(2, -5, TILE_EARTH);

  const auto initialMoves = sg.getAllPossibleMoves();
  cout << "Initial moves available: " << initialMoves.size() << endl;
  for (const auto move : initialMoves) {
      PlacedTile t1 = move.first;
      PlacedTile t2 = move.second;
      cout << "  [(" << t1.first.a << "," << t1.first.b << ") "
           << t1.second.type << "] + ";
      cout << "[(" << t2.first.a << "," << t2.first.b << ") "
           << t2.second.type << "]" << endl;
    }

  Solution sol = sg.solve();

  if (sol.first) {
    cout << "Solver completed successfully!" << endl;

    size_t i = 1;
    for (const auto move : sol.second) {
      PlacedTile t1 = move.first;
      PlacedTile t2 = move.second;
      cout << "  " << i << ") [(" << t1.first.a << "," << t1.first.b << ") "
           << t1.second.type << "] + ";
      cout << "[(" << t2.first.a << "," << t2.first.b << ") "
           << t2.second.type << "]" << endl;
      ++i;
    }
  } else {
    cout << "Solver failed!" << endl;
  }

  return 0;
}
