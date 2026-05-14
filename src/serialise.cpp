#include <stdexcept>
#include "puzzle.h"

constexpr std::uint16_t MAGIC_NUMBER = 0x4F01;

typedef struct __attribute__((packed)) {
  std::int16_t a;
  std::int16_t b;
  std::uint8_t type;
} SerialisedTile;

typedef struct __attribute__((packed)) {
  std::uint16_t magic_number;
  std::uint32_t num_tiles;
  SerialisedTile tiles[];
} SerialisedPuzzle;

std::size_t
SigmarsGarden::serialise(const std::size_t bufsize, void *buf) {
  const std::size_t num_tiles = tiles.size();
  const std::size_t bytes_required = sizeof(SerialisedPuzzle) + num_tiles*sizeof(SerialisedTile);
  if (bytes_required > bufsize) {
    return 0;
  }

  // build the serialisation
  SerialisedPuzzle *output = (SerialisedPuzzle*)buf;
  output->magic_number = MAGIC_NUMBER;
  output->num_tiles = num_tiles;

  std::size_t i = 0;
  for (const auto iter : tiles) {
    output->tiles[i].a = iter.first.a;
    output->tiles[i].b = iter.first.b;
    output->tiles[i].type = iter.second.type;
    ++i;
  }

  return bytes_required;
}

// initialise puzzle by deserialising
SigmarsGarden::SigmarsGarden(const void *buf) {
  const SerialisedPuzzle *p = (const SerialisedPuzzle*)buf;

  if (p->magic_number != MAGIC_NUMBER) throw std::invalid_argument("bad magic number");

  for (std::size_t i = 0; i < p->num_tiles; ++i) {
    const SerialisedTile &t = p->tiles[i];
    tiles[Coord(t.a, t.b)] = Tile((TileType)t.type);
  }
}
