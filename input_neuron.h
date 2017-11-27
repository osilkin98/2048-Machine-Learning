#ifndef INPUT_NEURON_H
#define INPUT_NEURON_H
#include "neuron.h"

class InputNeuron : public virtual Neuron{
 private:
  long double value;
 public:
 InputNeuron(void) : value(0) { }
 InputNeuron(const long double val)
   : value(val) { }

  // basic I/O function
  void input(const unsigned long value);

  
  inline long double activation(void) const { return value; }
  
};

#endif
