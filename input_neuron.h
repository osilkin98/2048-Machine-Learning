#ifndef INPUT_NEURON_H
#define INPUT_NEURON_H
#include "neuron.h"

class InputNeuron : public virtual Neuron{
  //private:
  //long double value;
 public:
 InputNeuron(void) : Neuron(0) { }
 InputNeuron(const double long val)
   : Neuron(val) { }
  
  // basic I/O function
  inline void input(const double long  val) { value = val; }
  inline void input(const unsigned long val) {
    value = static_cast<double long>(val);
  }
  
  inline double long activation(void) const { return value; }
  
};

#endif
