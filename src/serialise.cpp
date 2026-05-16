#include <stdexcept>
#include "puzzle.h"

// portable way of packing the struct
// https://stackoverflow.com/a/3312896
#ifdef __GNUC__
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif

#ifdef _MSC_VER
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop))
#endif

constexpr std::uint16_t MAGIC_NUMBER = 0x4F01;

typedef PACK(struct {
  std::int16_t a;
  std::int16_t b;
  std::uint8_t type;
}) SerialisedTile;

typedef PACK(struct {
  std::uint16_t magic_number;
  std::uint32_t num_tiles;
  SerialisedTile tiles[];
}) SerialisedPuzzle;

std::size_t SigmarsGarden::serialise_required_buf_size() const {
  const std::size_t num_tiles = tiles.size();
  return sizeof(SerialisedPuzzle) + num_tiles*sizeof(SerialisedTile);
}

std::size_t
SigmarsGarden::serialise(const std::size_t bufsize, void *buf) const {
  const std::size_t bytes_required = serialise_required_buf_size();
  if (bytes_required > bufsize) {
    return 0;
  }

  // build the serialisation
  SerialisedPuzzle *output = (SerialisedPuzzle*)buf;
  output->magic_number = MAGIC_NUMBER;
  output->num_tiles = tiles.size();

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
