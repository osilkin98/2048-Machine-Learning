#include "input_neuron.h"

// input function reads a value from the tile and
// stores that value in the object
void InputNeuron::input(const unsigned long val) {
  value = static_cast<long double>(val);
}


