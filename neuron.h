#ifndef NEURON_H
#define NEURON_H

class Neuron {
 protected:
  double long value;
 public:
 Neuron(void) : value(0) {} 
 Neuron(const double long val) : value(val) {}
 
  virtual double long activation(void) const = 0;

  virtual void input(const double long val) = 0;
};


#endif
