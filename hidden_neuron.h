#ifndef HIDDEN_NEURON_H
#define HIDDEN_NEURON_H
#include "neuron.h"

class HiddenNeuron : public virtual Neuron {
  //private:
  //double long value;
 public:
  HiddenNeuron(void);
  HiddenNeuron(const double long val);
  // 
  // activation function that takes the stored value
  // and squashes it and returns it
  virtual double long activation(void) const;

  virtual void input(double long val);
};

#endif
