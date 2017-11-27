#include "output_neuron.h"
#include <cmath>

OutputNeuron::OutputNeuron(void) : value(0) { }

OutputNeuron::OutputNeuron(const double long val)
  : value(val) { }

inline double long OutputNeuron::activation(void) const {
  return 1 / (1 + exp((-1)*value));
}

inline void OutputNeuron::input(double long val) {
  value = val;
}
