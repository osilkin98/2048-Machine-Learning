#ifndef NEURALNET_H
#define NEURALNET_H
#include <vector>
#include "grid.h"
#include "neuron.h"
#include "hidden_neuron.h"
#include "input_neuron.h"
#include "output_neuron.h"

class NeuralNet {
 private:
  // neuron layers

  // 16x1 neurons 
  std::vector<InputNeuron*> input_layer;
  // 12x1 neurons
  std::vector<HiddenNeuron*> hidden_layer1;
  // 8x1 neurons
  std::vector<HiddenNeuron*> hidden_layer2;
  // 4x1 neurons
  std::vector<OutputNeuron*> output_layer;

  /**** weight vectors ****/
  // size=16x12
  std::vector< std::vector<double long> > weights_l12;
  // size=12x8
  std::vector< std::vector<double long> > weights_l23;
  // size=8x4
  std::vector< std::vector<double long> > weights_l34;
  
  /**** bias vectors ****/
  // size=12x1
  std::vector<double long> bias_l12;
  // size=8x1
  std::vector<double long> bias_l23;
  // size=4x1
  std::vector<double long> bias_l34;
  void initialize(bool);
 public:
  NeuralNet(void);
  NeuralNet(const NeuralNet & other);
  // this is going to be called whenever the
  // current neural network is going to be kicked out
  // of its current population
  ~NeuralNet(void);

  void mutate(double rand);

  // member function to receive the current state
  // of a grid object and compute an output from {1,2,3,4}
  short compute_output(Grid & game) const;

  
  
};

#endif
