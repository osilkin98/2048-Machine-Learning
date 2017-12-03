#include "tile.h"
#include <cstdlib>
#include <iostream> // this is required for ssize_t

// this constructor will be used always
Tile::Tile(void) : value((rand() % 2) + 1){ }

Tile::Tile(const unsigned long val) : value(val) { }

Tile::Tile(const Tile & other) : value(other.value),
				 merged(other.merged) { }

bool Tile::set_merged(bool val) {
  merged = val;
  return merged;
}

Tile& Tile::operator++(void) {
  value *= 2;
  return *this;
}

inline void Tile::increment_value(void) {
  value *= 2;
}
