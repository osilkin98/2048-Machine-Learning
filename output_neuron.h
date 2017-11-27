#ifndef OUTPUT_NEURON_H
#define OUTPUT_NEURON_H
#include "neuron.h"

class OutputNeuron : public virtual Neuron {
  //private:
  double long value;
 public:
  OutputNeuron(void);
  OutputNeuron(const double long val);

  // this should return a value between 0 & 1
  virtual double long activation(void) const;

  // vector multiplication of the weight vector
  // and all the values of the last layer
  // with an additional corresponding bias
  // added onto the end.
  virtual void input(double long val);
};

#endif
