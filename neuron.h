#ifndef NEURON_H
#define NEURON_H

class Neuron {
 private:
  double long value;
 public:
  Neuron(void);
  //Neuron(const double long val);

  virtual double long activation(void) const =0;

  virtual void input(double long val);
};


#endif
