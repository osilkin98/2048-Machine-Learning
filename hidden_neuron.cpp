#include "hidden_neuron.h"
#include <cstdlib>
#include <cmath>

HiddenNeuron::HiddenNeuron(void)
  : value(pow(-1, rand()) * static_cast<double>(rand())/static_cast<double>(RAND_MAX)){}

HiddenNeuron::HiddenNeuron(const double long val) : value(val) { }

inline void HiddenNeuron::input(double long val) { value = val; }

inline double long HiddenNeuron::activation(void) const {
  return 1/(1 + exp((-1)*value));
}

