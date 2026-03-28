#include "puzzle.h"
#include "tile_type.h"
#include <iostream>

using namespace std;

int main() {
  SigmarsGarden sg = SigmarsGarden();

  sg.setTile(0, 0, TILE_GOLD);
  sg.setTile(0, 1, TILE_QUICKSILVER);
  sg.setTile(1, 0, TILE_FIRE);
  sg.setTile(-1, 0, TILE_FIRE);

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
