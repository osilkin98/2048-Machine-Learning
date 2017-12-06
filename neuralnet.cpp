#include "neuralnet.h"
#include <vector>
#include <cstdlib>
#include <random>

#define RAND_CONST 0.15

NeuralNet::NeuralNet(void)
  : fitness(1), input_layer(16),
    hidden_layer1(12), hidden_layer2(8),
    output_layer(4),
    weights_l12(16, std::vector<double long>(12)),
    weights_l23(12, std::vector<double long>(8)),
    weights_l34(8, std::vector<double long>(4)),
    bias_l12(12), bias_l23(8), bias_l34(4) {
  this -> initialize(true);
}

NeuralNet::~NeuralNet(void) {
  for(size_t i = 0; i < input_layer.size(); ++i) {
    delete input_layer[i];
    input_layer[i] = NULL;
  }
  for(size_t i = 0; i < hidden_layer1.size(); ++i) {
    delete hidden_layer1[i];
    hidden_layer1[i] = NULL;
  }
  for(size_t i = 0; i < hidden_layer2.size(); ++i) {
    delete hidden_layer2[i];
    hidden_layer2[i] = NULL;
  }
  for(size_t i = 0; i < output_layer.size(); ++i) {
    delete output_layer[i];
    output_layer[i] = NULL;
  }
  /*
  input_layer.clear();
  input_layer.swap(std::vector<InputNeuron*>(input_layer));
  hidden_layer1.clear();
  hidden_layer2.swap(std::vector<HiddenNeuron*>(hidden_layer1));
  hidden_layer2.clear();
  hidden_layer2.swap(std::vector<HiddenNeuron*>(hidden_layer2));
  output_layer.clear();
  output_layer.swap(std::vector<OutputNeuron*>(output_layer));
  typedef size_t st;
  typedef double long dl;
  for(st i = 0; i < weights_l12.size(); ++i) {
    weights_l12[i].clear();
    weights_l12[i].swap(std::vector<dl>(weights_l12[i]));
  }
  weights_l12.clear();
  weights_l12.swap(std::vector< std::vector<dl> >(weights_l12));
  for(st i = 0; i < weights_l23.size(); ++i) {
    weights_l23[i].clear();
    weights_l23[i].swap(std::vector<dl>(weights_l23[i]));
  }
  weights_l23.clear();
  weights_l23.swap(std::vector< std::vector<dl> >(weights_l23));
  for(st i = 0; i < weights_l34.size(); ++i) {
    weights_l34[i].clear();
    weights_l34[i].swap(std::vector<dl>(weights_l34[i]));
  }
  weights_l34.clear();
  weights_l34.swap(std::vector< std::vector<dl> >(weights_l34));

  bias_l12.clear();
  bias_l23.swap(std::vector<dl>(bias_l12));
  bias_l23.clear();
  bias_l23.swap(std::vector<dl>(bias_l23));
  bias_l34.clear();
  bias_l34.swap(std::vector<dl>(bias_l34));
  */
}

// this constructor is for the purpose of
// recombination; nets will consist of two
// (or more) neual networks which 
NeuralNet::NeuralNet(const std::vector<NeuralNet*> nets)
  : input_layer(16), hidden_layer1(12),
    hidden_layer2(8), fitness(1),
    output_layer(4),
    weights_l12(16, std::vector<double long>(12)),
    weights_l23(12, std::vector<double long>(8)),
    weights_l34(8, std::vector<double long>(4)),
    bias_l12(12), bias_l23(8), bias_l34(4) {
  for(size_t i = 0; i < 16; ++i) {
    for(size_t j = 0; j < 12; ++j) {
      if(static_cast<double>(rand())
	 /static_cast<double>(RAND_MAX) <= 0.5) {
	weights_l12[i][j] = nets[0] -> weights_l12[i][j];
      } else {
	weights_l12[i][j] = nets[1] -> weights_l12[i][j];
      }
    }
  }
  for(size_t i = 0; i < 12; ++i) {
    for(size_t j = 0; j < 8; ++j) {
      if(static_cast<double>(rand())/
	 static_cast<double>(RAND_MAX) <= 0.5) {
	weights_l23[i][j] = nets[0] -> weights_l23[i][j];
      } else {
	weights_l23[i][j] = nets[1] -> weights_l23[i][j];
      }
    }
  }
  for(size_t i = 0; i < 8; ++i) {
    for(size_t j = 0; j < 4; ++j) {
      if(static_cast<double>(rand())/
	 static_cast<double>(RAND_MAX) <= 0.5) {
	weights_l34[i][j] = nets[0] -> weights_l34[i][j];
      } else {
	weights_l34[i][j] = nets[1] -> weights_l34[i][j];
      }
    }
  }
  for(size_t i = 0; i < 12; ++i) {
    if(static_cast<double>(rand())/
       static_cast<double>(RAND_MAX) <= 0.5) {
      bias_l12[i] = nets[0] -> bias_l12[i];
    } else {
      bias_l12[i] = nets[1] -> bias_l12[i];
    }
  }
  for(size_t i = 0; i < 8; ++i) {
    if(static_cast<double>(rand())/
       static_cast<double>(RAND_MAX) <= 0.5) {
      bias_l23[i] = nets[0] -> bias_l23[i];
    } else {
      bias_l23[i] = nets[1] -> bias_l23[i];
    }
  }
  for(size_t i = 0; i < 4; ++i) {
    if(static_cast<double>(rand())/
       static_cast<double>(RAND_MAX) <= 0.5) {
      bias_l34[i] = nets[0] -> bias_l34[i];
    } else {
      bias_l34[i] = nets[1] -> bias_l34[i];
    }
  }
  
  this -> initialize(false);
}

// to initialize the neural network
void NeuralNet::initialize(bool is_new = true) {
  if(is_new) {
    this -> mutate(1.0);
  } else {
    this -> mutate(0.15);
  }
  
  for(size_t i = 0; i < input_layer.size(); ++i){
    InputNeuron* temp = NULL;
    temp = new InputNeuron;
    if(temp != NULL) {
      input_layer[i] = temp;
    } else {
      std::cerr << "the allocation failed " <<
	"on InputNeuron_" << i+1 << "\n";
      return;
    }
  }
  for(size_t i = 0; i < hidden_layer1.size(); ++i) {
    HiddenNeuron* temp = NULL;
    temp = new HiddenNeuron;
    if(temp != NULL) {
      hidden_layer1[i] = temp;
    } else {
      std::cerr << "the allocation of HiddenNeuron"
		<< "_" << i+1 << " failed\n";
      return;
    }
  }
  for(size_t i = 0; i < hidden_layer2.size(); ++i) {
    HiddenNeuron* temp = NULL;
    temp = new HiddenNeuron;
    if(temp != NULL) {
      hidden_layer2[i] = temp;
    } else {
      std::cerr << "the allocation of HiddenNeuron_"
		<< i+1 << " has failed!\n";
      return;
    }
  }
  for(size_t i = 0; i < output_layer.size(); ++i) {
    OutputNeuron* temp = NULL;
    temp = new OutputNeuron;
    if(temp != NULL) {
      output_layer[i] = temp;
    } else {
      std::cerr << "the allocation of OutputNeuron_"
		<< i+1 << " failed\n";
      return;
    }
  }
}

// function should randomly alter the
// weights and biases
void NeuralNet::mutate(double const
		       rand_const = RAND_CONST) {
  std::default_random_engine generator(time(0));
  std::normal_distribution<double long> norm_dist(0.0, 2.0);
  for(size_t i = 0; i < weights_l12.size(); ++i) {
    for(size_t j = 0; j < weights_l12[i].size(); ++j) {
      if(static_cast<double>(rand())/
	 static_cast<double>(RAND_MAX) <= rand_const) {
	weights_l12[i][j] = norm_dist(generator);
      }
    }
  }
  for(size_t i = 0; i < weights_l23.size(); ++i) {
    for(size_t j = 0; j < weights_l23[i].size(); ++j) {
      if(static_cast<double>(rand())/
	 static_cast<double>(RAND_MAX) <= rand_const) {
	weights_l23[i][j] = norm_dist(generator);
      }
    }
  }
  for(size_t i = 0; i < weights_l34.size(); ++i) {
    for(size_t j = 0; j < weights_l34[i].size(); ++j) {
      if(static_cast<double>(rand())/
	 static_cast<double>(RAND_MAX) <= rand_const) {
	weights_l34[i][j] = norm_dist(generator);
      }
    }
  }
  for(size_t i = 0; i < bias_l12.size(); ++i) {
    if(static_cast<double>(rand())/
       static_cast<double>(RAND_MAX) <= rand_const) {
      bias_l12[i] = norm_dist(generator);
    }
  }
  for(size_t i = 0; i < bias_l23.size(); ++i){
    if(static_cast<double>(rand())/
       static_cast<double>(RAND_MAX) <= rand_const) {
      bias_l23[i] = norm_dist(generator);
    }
  }
  for(size_t i = 0; i < bias_l34.size(); ++i) {
    if(static_cast<double>(rand())/
       static_cast<double>(RAND_MAX) <= rand_const) {
      bias_l34[i] = norm_dist(generator);
    }
  }
}

short NeuralNet::compute_output(const Grid & game) const{
  //std::cerr << "computing output for input layer.\n";
  // to set the values for each input neuron
  for(size_t i = 0; i < game.board_size(); ++i) {
    for(size_t j = 0; j < game.board_size(); ++j) {
      input_layer[game.board_size()*i + j] ->
	input(game.get_value_at(i, j));
    }
  }
  // to pass the values from the input layer to the
  // first hidden layer.
  // L_2 = INPUT_LAYER_TRANS x WEIGHTS_L12 + B_L12
  //std::cerr << "computing hidden layer 1.\n";
  for(size_t neuron = 0;
      neuron < hidden_layer1.size(); ++neuron) {
    double long s = 0;
    for(size_t inp = 0; inp < input_layer.size(); ++inp) {
      s += (input_layer[inp] -> activation()) *
	weights_l12[inp][neuron];
    
    }
    hidden_layer1[neuron] -> input(s + bias_l12[neuron]);
  }


  //std::cerr << "computing hidden layer 2\n";
  // computes the forward-pass for the 3rd layer
  // LAYER_3 = transpose(LAYER_2) x WEIGHTS_L23 + BIAS_L23
  for(size_t neuron = 0; neuron < hidden_layer2.size(); ++neuron) {
    double long s = 0;
    for(size_t inp = 0; inp < hidden_layer1.size(); ++inp) {
      s += (hidden_layer1[inp] -> activation()) *
	weights_l23[inp][neuron];
    }
    hidden_layer2[neuron] -> input(s + bias_l23[neuron]);
  }

  //std::cerr << "computing output layer\n";
  // computes the output layer by performing the matrix muliplication
  // output = hidden_layer2 x weights_layer_34 + bias_layer_34
  for(size_t neuron = 0; neuron < output_layer.size(); ++neuron) {
    double long s = 0;
    for(size_t inp = 0; inp < hidden_layer2.size(); ++inp) {
      s += (hidden_layer2[inp] -> activation()) *
	weights_l34[inp][neuron];
    }
    output_layer[neuron] -> input(s + bias_l34[neuron]);
  }
  
  size_t max_ind = 0;
  for(size_t i = 1; i < output_layer.size(); ++i) {
    if((output_layer[i] -> activation()) >
       (output_layer[i-1] -> activation())) {
      max_ind = i;
    }
  }
  return static_cast<short>(max_ind);
}

