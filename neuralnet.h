#ifndef NEURALNET_H
#define NEURALNET_H
#include <vector>
#include <iostream>
#include <fstream>
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

 public:

  // the turns variable keeps count of how many turns
  // the neural network has taken
  // which allows us to calculate how well it actually
  // performs
  unsigned long turns;
  double fitness;
  bool stuck;
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
  //short identifier;
  NeuralNet(void);
  NeuralNet(const std::vector<NeuralNet*> & nets);
  // this is going to be called whenever the
  // current neural network is going to be kicked out
  // of its current population
  ~NeuralNet(void);

  void mutate(double rand);

  // member function to receive the current state
  // of a grid object and compute an output from {1,2,3,4}
  short compute_output(const Grid & game) const;

  void write_vector(std::ostream & outs,
		    const std::vector<double long> & vec,
		    const char* name) const {
    outs << name << "\n";
    for(size_t i = 0; i < vec.size(); ++i) {
      outs << vec[i] << " ";
    }
    outs << "\n\n";
  }
  
  void write_matrix(std::ostream & outs,
		    const std::vector< std::vector<double long> > mat,
		    const char* name) const {
    outs << name << "\n";
    for(size_t i = 0; i < mat.size(); ++i) {
      for(size_t j = 0; j < mat[i].size(); ++j) {
	outs << mat[i][j] << " ";
      }
      outs << "\n";
    }
    outs << "\n\n";
  }

    
  bool dump_values(void) const {
    std::ofstream dump_file("weights_biases.txt");
    if(dump_file) {
      write_matrix(dump_file, weights_l12, "weights L_12");
      write_matrix(dump_file, weights_l23, "weights L_23");
      write_matrix(dump_file, weights_l34, "weights L_34");
      write_vector(dump_file, bias_l12, "bias L_12");
      write_vector(dump_file, bias_l23, "bias L_23");
      write_vector(dump_file, bias_l34, "bias L_34");
    } else {
      dump_file.close();
      std::cerr << "writing has failed, dumping.\n";
      write_matrix(std::cout, weights_l12, "weights L_12");
      write_matrix(std::cout, weights_l23, "weights L_23");
      write_matrix(std::cout, weights_l34, "weights L_34");
      write_vector(std::cout, bias_l12, "bias L_12");
      write_vector(std::cout, bias_l23, "bias L_23");
      write_vector(std::cout, bias_l34, "bias L_34");
      return false;
    }
    dump_file.close();
    return true;
  }
};

#endif
