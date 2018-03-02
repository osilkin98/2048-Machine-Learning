#include "grid.h"
#include "neuralnet.h"
#include "neural_manager.h"
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <string> 

#define NUM_FITTEST 2
#define NETWORK_CAPACITY 150

GeneticAlgorithm::GeneticAlgorithm(void) :
  networks(NETWORK_CAPACITY), games(NETWORK_CAPACITY),
  max_score(0), best_candidates(2, 8), generation(0),
  local_max_score(0), local_max_turns(0), max_turns(0) {
  /*for(short i = 0; i < NETWORK_CAPACITY; ++i) {
    networks[i] = new NeuralNet;
    games[i] = new Grid;
    }*/
}

// just a basic struct to compare the fitness values between
// two different neural networks regardless of defined function
struct compare_fitness {
  bool operator()(NeuralNet* & n1, NeuralNet* & n2) {
    return n1 -> score < n2 -> score;
  }
} comp_func;


// obsolete
struct compare_score {
  bool operator()(Grid* & c1, Grid* & c2) {
    return c1 -> get_score() < c2 -> get_score();
  }
} score_comp;

// sorts the neural networks from lowest to highest in terms
// of fitness value
void GeneticAlgorithm::sort_population(void) {
  // since the fitness function just compares the turns taken
  std::sort(networks.begin(), networks.end(), comp_func);
  // let's just not sort it by score because it'll be misleading
  //std::sort(games.begin(), games.end(), score_comp);
}


// evaluates the fitness based on the maximum score attained
void GeneticAlgorithm::evaluate_fitness(void) {
  for(register size_t i = 0; i < NETWORK_CAPACITY; ++i) {
    networks[i] -> fitness =
      static_cast<double>(networks[i] -> score)/
      static_cast<double>(max_score);
  }
  GeneticAlgorithm::sort_population();
}

// destructor for the GA
GeneticAlgorithm::~GeneticAlgorithm(void) {
  for(register size_t i = 0; i < NETWORK_CAPACITY; ++i) {
    delete networks[i];
    networks[i] = NULL;
    delete games[i];
    games[i] = NULL;
  }
}

void GeneticAlgorithm::generate_new_games(void) {
  // delete old games and instatiate them with
  // new ones.
  for(register size_t i = 0; i < NETWORK_CAPACITY; ++i) {
    if(games[i] != NULL) {
      delete games[i];
      games[i] = NULL;
    }
    games[i] = new Grid;
  }
}

// creates a new generation for the next iteration
void GeneticAlgorithm::new_generation(void) {
  // if we're only on the first generation then we can just
  // instantiate it normally 
  if(generation == 0) {
    for(register size_t i = 0; i < NETWORK_CAPACITY; ++i) {
      networks[i] = new NeuralNet;
    }
  } else {
    std::vector<NeuralNet*> nets(NUM_FITTEST);
    for(short i = 0; i < NUM_FITTEST; ++i) {
      std::cerr << "fitness of network["
		<< NETWORK_CAPACITY-(i+1) << "]: "
		<< networks[NETWORK_CAPACITY - (i + 1)] -> fitness
		<< "\nScores";
      nets[i] = networks[NETWORK_CAPACITY - (i + 1)];
    }
    // loops through and reproduces the neural
    // networks unless the index is the same as
    // that of the parents who's genes will be
    // copied and replicated
    for(register size_t i = 0; i < NETWORK_CAPACITY - NUM_FITTEST; ++i) {
      delete networks[i];
      networks[i] = NULL;
      networks[i] = new NeuralNet(nets);
    }
    for(short i = 0; i < NUM_FITTEST; ++i) {
      nets[i] = NULL;
    }
  }
  GeneticAlgorithm::generate_new_games();
  ++generation;
}

bool GeneticAlgorithm::play_game(NeuralNet * & curr,
				 Grid * & game, const size_t i) {
  std::ifstream infile("data.txt");
  if(infile) {
    short move = 0;
    unsigned long current_turns = 0;
    short next_val = 0;
    // while the tiles on the board can be merged in some way
    while(game -> has_merge()) {
      move = curr -> compute_output(*game);
      if(!(game -> take_turn(move))) {
	// since the neural net will continue computing the
	// same value because the tiles on the board are not
	// changing, there is nothing more that the neural network
	// can do. therefore we should exit the loop
	// and move onto  the next.
	curr -> turns = current_turns;
	curr -> stuck = true;
	break;
      }
      ++current_turns;
      // place a new tile after the game itself has taken a new turn
      infile >> next_val;
      game -> place_tile(next_val);
    }
    curr -> score = game -> get_score();
    
    // if the score attained from this algorithm is
    // better than the current highest score, replace it
    if(game -> get_score() >= local_max_score) {
      local_max_score = game -> get_score();
      ///best_candidates[0] = i;
    }
    if(current_turns > local_max_turns) {
      local_max_turns = current_turns;
    }
  }
  infile.close();
}

// chooses the best candidates to produce the next gen
void GeneticAlgorithm::select_best_candidates(void) {
  /*unsigned long second_score = 0;
  //best_candidates[1] = 0;
  for(size_t i = 0; i < NETWORK_CAPACITY; ++i) {
    // to find the second fittest candidate in our set

    // if the second greatest score is less than
    // the score of the current element, and the current
    // element is not the same as the first one,
    if(second_score <= games[i] -> get_score() &&
       i != best_candidates[0]) {

      // then update the second score to be equal to
      // that of what was just discovered
      second_score = games[i] -> get_score();

      // and change the index of the 2nd best candidate
      // to be the index of the current score
      best_candidates[1] = i;
    }
    }*/
  // the num fittest here will always be two
  // for the sake of the current recombination
  // algorithm
  for(register size_t i = 0; i < NUM_FITTEST; ++i) {
    best_candidates[i] = NETWORK_CAPACITY - (i + 1);
  }
}

void GeneticAlgorithm::print_scores(void) const {
  for(short i = 0; i < NETWORK_CAPACITY; ++i) {
    std::string status = networks[i] -> stuck ? "[STUCK] " : "[FINISHED] ";
    std::cerr << status << "Network-" << i << " - f: "
	      << std::setw(6)
	      << networks[i] -> fitness << "\tscore: "
	      << std::setw(6)
	      << games[i] -> get_score() << "\tturns: "
	      << networks[i] -> turns << "\n";
    
  }
  std::cerr << "\n\n";
}

// serves as the real main function to the
// genetic algorithm.
bool GeneticAlgorithm::train(void) {
  typedef GeneticAlgorithm GA;
  while(!critereon(max_score)) {
    // reset local maximums
    local_max_score = 0;
    local_max_turns = 0;
    // instantiate a new generation of neural networks
    GA::new_generation();

    std::cerr << "created new generation on iteration " << generation << "\n";

    for(size_t i = 0; i < NETWORK_CAPACITY; ++i) {

      // each new neural network generated must play
      // their corresponding instance of a 2048 game
      GA::play_game(networks[i], games[i], i);


      //std::cerr << "each of the networks played the game.\n";
      //GA::print_scores();
    }
    max_turns = local_max_turns > max_turns ? local_max_turns : max_turns;
    GA::evaluate_fitness();
    max_score = local_max_score > max_score ? local_max_score : max_score;
    
    
    std::cerr << "all of  the networks played the game:\n";
    GA::print_scores();
    // the genetic algorithm then selects the best
    // candidates to be reproduced in the next generation
    GA::select_best_candidates();
    
    std::cerr << "1st score [network-" << best_candidates[0]
	      << "]: " << std::setw(6)
	      << games[best_candidates[0]] -> get_score()
	      << "\n2nd score[network-" << best_candidates[1]
	      << "]: " << std::setw(6)
	      << games[best_candidates[1]] -> get_score()
	      << "\niteration[" << generation << "]\t"
	      << "maximum value attained: "<< max_score << std::setw(10)
	      << "\nMaximum turns reached: " << std::setw(5)
	      << max_turns << "\n\n";
    // for debugging
    getchar();
  }
  if(!(networks[best_candidates[0]] -> dump_values())) {
    std::cerr << "[CRITICAL ERROR]: Neural network failed "
	      << "to dump values. Exiting.\n";
    return false;
  } else {
    std::cerr << "[SUCCESS]: Neural Network successfully "
	      << "dumped files.\nExiting...\n";
    return true;
  }
}

int main() {
  GeneticAlgorithm ga;
  ga.train();
  //Grid game;
  //short s = 0;
  /*
    while(game.has_merge()) {
    game.print(std::cout);
    s = nn.compute_output(game);
    std::cout << "Computed output: " << s << std:
    }:endl;
    game.take_turn(s);
    game.place_tile();
    }
    std::cout << "Game over! " << std::endl;
    game.print(std::cout);
    std::cout << "score: " << game.get_score() << std::endl;
  */
  return 0;
}
