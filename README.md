# SigmarSolver

A solving library for the Sigmar's Garden minigame of _Opus Magnum_, written in C++.

## Features

 - **Complete game implementation**: Includes marble matching rules, marble unlocking rules, and the metal sequence.
 - **Efficient solver**: Solves most puzzles in under a second on typical laptop hardware using a randomised depth-first search with a limit on number of states explored.
 - **C++ objects**: Complete library API and game rules available in C++ via native classes.
 - **C API**: Minimal, stable C interface, enabling use of the solver from C and other languages.
 - **Python bindings**: ctypes-based bindings for the C API, with pre-built wheels for easy installation.
 
## Installation

Pre-built shared libraries are available for 64-bit Windows and Linux. These can be downloaded from the [releases](../../releases) page. Simply link against these pre-built libraries to use them in your own code.

Pre-built wheels for the Python bindings are also available for these platforms. These can be installed with pip.

For other platforms, see the building instructions below.

## Building

The library does not require any additional libraries, and requires only CMake for building. See below for installing the required packages.

<details>
  <summary><b>Ubuntu</b></summary>

  ```bash
  sudo apt install build-essential cmake
  ```
</details>

Building the library is straightforward. Either download and extract a source archive from the [releases](../../releases) page, or clone the git repository:

```bash
git clone https://github.com/joshbarrass/SigmarSolver.git
```

Then build the library:

```bash
cmake -B build SigmarSolver
cmake --build build --config Release
```

### Python

The Python bindings can also be installed directly from the source code, and the library will be built as part of the installation process. Simply download the source code as above, and then run

```bash
pip install SigmarSolver/python
```

## Implementation Details

### Hexagonal Coordinate System

Since Sigmar's Garden is played on a hexagonal grid, the library uses a hexagonal coordinate system for setting up puzzles. The axes of this coordinate system are shown below.

<a href="../files/hexagonal_coords.png" ><img src="../files/hexagonal_coords_small.png" width=250 /></a>

Essentially, the first coordinate acts like the Cartesian x coordinate, moving you horizontally left and right (consistent with θ = 0° in polar coordinates). The second coordinate moves you up-and-right at a 60 degree angle (consistent with θ = 60° in polar coordinates). The origin, (0, 0), can be chosen arbitrarily, but it is common to define the centre of the puzzle as (0, 0). 

## Usage

The library exposes two interfaces for using it in your own code:

  1) A minimal, but stable, C API, which should be considered the gold standard for compatibility between compilers.
  2) A full C++ API, which allows greater, more natural access to the library's features, but is not guaranteed to have a stable ABI.

The C interface is simplest to use, and is sufficient for building a puzzle and invoking the solver. If you need to access more of the internal types and methods, the C++ API should be used.

### C

The only header required to use the C API is [`sigmarsolver.h`](include/sigmarsolver.h). This header is completely self-contained, so you can download just this header and include it in your code. It is also relatively short, and the functions exposed here all have comments describing their basic usage.

The basic usage steps for the C API are:

  1) Call `sigmarsgarden_init()` to get an opaque puzzle context. This will be a pointer to the underlying C++ object, allocated on the heap.
  2) Use `sigmarsgarden_setTile` to add marbles to the puzzle. The first argument is your puzzle context, and the remaining arguments are the two components of the coordinate (using [hexagonal coordinates](#hexagonal-coordinate-system)), and the type of the marble (see the `TileType` enum).
  3) Call `sigmarsgarden_solve` to get a solution. The only argument is your puzzle context. This returns a pointer to a solution struct, which contains the moves required to solve the puzzle (or a null pointer if no solution was found). This is allocated on the heap -- the caller is responsible for freeing this.
  4) When you are done with your solution, use `sigmarsolution_free` to free it. At present, this is just a wrapper for `free`, but it is exposed for completeness and for use in other languages.
  5) When you are done with your puzzle context, use `sigmarsgarden_free` to free it.

A basic example is provided below. You can also see [`test.c`](test.c) for a complete example, including parsing the solution struct and printing the solution.

```C
#include "sigmarsolver.h"

int main() {
  // create the puzzle context
  void *sg = sigmarsgarden_init();

  // add the marbles to the puzzle
  sigmarsgarden_setTile(sg, 0, 0, TILE_GOLD);
  sigmarsgarden_setTile(sg, 1, 0, TILE_FIRE);
  sigmarsgarden_setTile(sg, -1, 0, TILE_FIRE);
  // ...

  // get the solution
  SigmarSolution *sol = sigmarsgarden_solve(sg);
  if (sol == NULL) {
    // sol is NULL if no solution was found
    return 1;
  }
  // ... do whatever you need with it here!

  // clean up
  sigmarsolution_free(sol);
  sigmarsgarden_free(sg);

  return 0;
}
```

### C++

To use the C++ API, you will need all of the headers found in the [`include`](include) directory. You can check these headers to see a full list of all the functions available to you, but a basic example of how to use the API is shown below. You can also see [`test.cpp`](test.cpp) for a complete example.

```C++
#include <iostream>
#include "puzzle.h"
#include "tile_type.h"

int main() {

  // create the puzzle context. You can also pass a binary
  // representation of the puzzle to initialise it directly.
  SigmarsGarden sg = SigmarsGarden();
  
  // add the marbles to the puzzle
  sg.setTile(0, 0, TILE_GOLD);
  sg.setTile(1, 0, TILE_FIRE);
  sg.setTile(-1, 0, TILE_FIRE);
  // ...
  
  // get a list of all possible moves for the current state
  const std::vector<Move> allMoves = sg.getAllPossibleMoves();
  
  // get a tile at a particular coordinate
  const Tile t = sg.getTileAt(0, 0);
  
  // tile types can be printed directly
  std::cout << t.type << std::endl;
  // prints "GOLD"
  
  // get the solution
  Solution sol = sg.solve();
  if (!sol.first) {
    // sol.first is false if no solution was found
    return 1;
  }
  // ... do whatever you need with the list of moves
  // for (const auto move : sol.second) { ... }
  
  // no cleanup required for stack-allocated objects
  // destructors take care of everything
  
  return 0;
```
  
### Python

The Python bindings expose the C API functions through a more natural Python API. A basic example is provided below. You can also see [`test.py`](test.py) for a complete example.

```python
import sys
from sigmarsolver import SigmarsGarden, TileType

# create the puzzle context
sg = SigmarsGarden()

# add the marbles to the puzzle
sg.setTile(0, 0, TileType.GOLD)
sg.setTile(1, 0, TileType.FIRE)
sg.setTile(-1, 0, TileType.FIRE)
# ...

# get the solution
sol = sg.solve()
if not sol:
  # sol is None if no solution was found
  sys.exit(1)
# ... do whatever you need with it here!

# no manual cleanup required
# destructors take care of everything
```
