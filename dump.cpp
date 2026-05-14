#include "puzzle.h"
#include "tile_type.h"
#include <iostream>
#include <fstream>

using namespace std;

int main() {
  SigmarsGarden sg = SigmarsGarden();

  // https://bits.ondrovo.com/sigmar/?seed=1774706658890
  sg.setTile(0, 0, TILE_GOLD);
  sg.setTile(1, 0, TILE_WATER);
  sg.setTile(2, 0, TILE_DEATH);
  sg.setTile(3, 0, TILE_QUICKSILVER);
  sg.setTile(-1, 0, TILE_AIR);
  sg.setTile(-2, 0, TILE_WATER);
  sg.setTile(-3, 0, TILE_SALT);
  sg.setTile(0, 1, TILE_WATER);
  sg.setTile(1, 1, TILE_WATER);
  sg.setTile(2, 1, TILE_LIFE);
  sg.setTile(-1, 1, TILE_WATER);
  sg.setTile(-2, 1, TILE_LIFE);
  sg.setTile(-3, 1, TILE_WATER);
  sg.setTile(-4, 1, TILE_FIRE);
  sg.setTile(0, 2, TILE_AIR);
  sg.setTile(1, 2, TILE_FIRE);
  sg.setTile(2, 2, TILE_EARTH);
  sg.setTile(-1, 2, TILE_AIR);
  sg.setTile(-2, 2, TILE_DEATH);
  sg.setTile(-3, 2, TILE_SILVER);
  sg.setTile(-4, 2, TILE_FIRE);
  sg.setTile(-5, 2, TILE_EARTH);
  sg.setTile(0, 3, TILE_AIR);
  sg.setTile(1, 3, TILE_EARTH);
  sg.setTile(2, 3, TILE_FIRE);
  sg.setTile(-1, 3, TILE_QUICKSILVER);
  sg.setTile(-2, 3, TILE_AIR);
  sg.setTile(-3, 3, TILE_SALT);
  sg.setTile(-3, 4, TILE_SALT);
  sg.setTile(-2, 4, TILE_EARTH);
  sg.setTile(-3, 5, TILE_EARTH);
  sg.setTile(0, -1, TILE_FIRE);
  sg.setTile(1, -1, TILE_COPPER);
  sg.setTile(2, -1, TILE_EARTH);
  sg.setTile(3, -1, TILE_IRON);
  sg.setTile(4, -1, TILE_DEATH);
  sg.setTile(-1, -1, TILE_QUICKSILVER);
  sg.setTile(-2, -1, TILE_QUICKSILVER);
  sg.setTile(0, -2, TILE_TIN);
  sg.setTile(1, -2, TILE_LIFE);
  sg.setTile(2, -2, TILE_EARTH);
  sg.setTile(3, -2, TILE_WATER);
  sg.setTile(4, -2, TILE_LIFE);
  sg.setTile(5, -2, TILE_FIRE);
  sg.setTile(-1, -2, TILE_DEATH);
  sg.setTile(-2, -2, TILE_EARTH);
  sg.setTile(0, -3, TILE_SALT);
  sg.setTile(-1, -3, TILE_QUICKSILVER);
  sg.setTile(-2, -3, TILE_FIRE);
  sg.setTile(1, -3, TILE_WATER);
  sg.setTile(2, -3, TILE_AIR);
  sg.setTile(3, -3, TILE_LEAD);
  sg.setTile(3, -4, TILE_AIR);
  sg.setTile(2, -4, TILE_AIR);
  sg.setTile(3, -5, TILE_FIRE);

  char buf[500];
  size_t bytes_written = sg.serialise(500, buf);
  if (bytes_written == 0) {
    cout << "Buffer too small" << endl;
  }
  cout << "Wrote " << bytes_written << " bytes to buffer" << endl;

  ofstream file("puzzle.sgp", ios::out | ios::binary);
  file.write(buf, bytes_written);
  file.close();

  SigmarsGarden sg2((const void*)buf);

  const auto initialMoves = sg2.getAllPossibleMoves();
  cout << "Initial moves available: " << initialMoves.size() << endl;
  for (const auto move : initialMoves) {
      PlacedTile t1 = move.first;
      PlacedTile t2 = move.second;
      cout << "  [(" << t1.first.a << "," << t1.first.b << ") "
           << t1.second.type << "] + ";
      cout << "[(" << t2.first.a << "," << t2.first.b << ") "
           << t2.second.type << "]" << endl;
    }

  Solution sol = sg2.solve();

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
