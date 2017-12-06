#include "grid.h"
#include "neuralnet.h"
#include "neural_manager.h"
#include <vector>
#include <iomanip>
#include <fstream>

#define NETWORK_CAPACITY 8

GeneticAlgorithm::GeneticAlgorithm(void) :
  networks(NETWORK_CAPACITY), games(NETWORK_CAPACITY),
  max_score(0), best_candidates(2, 8), generation(0) {
  /*for(short i = 0; i < NETWORK_CAPACITY; ++i) {
    networks[i] = new NeuralNet;
    games[i] = new Grid;
    }*/
}

// destructor for the GA
GeneticAlgorithm::~GeneticAlgorithm(void) {
  for(size_t i = 0; i < NETWORK_CAPACITY; ++i) {
    delete networks[i];
    networks[i] = NULL;
    delete games[i];
    games[i] = NULL;
  }
}

void GeneticAlgorithm::generate_new_games(void) {
  // delete old games and instatiate them with
  // new ones.
  for(size_t i = 0; i < NETWORK_CAPACITY; ++i) {
    if(games[i] != NULL) {
      delete games[i];
      games[i] = NULL;
    }
    games[i] = new Grid;
  }
}

void GeneticAlgorithm::new_generation(void) {
  if(generation == 0) {
    for(size_t i = 0; i < NETWORK_CAPACITY; ++i) {
      networks[i] = new NeuralNet;
    }
  } else {
    std::vector<NeuralNet*> nets(2);
    nets[0] = networks[best_candidates[0]];
    nets[1] = networks[best_candidates[1]];
    // loops through and reproduces the neural
    // networks unless the index is the same as
    // that of the parents who's genes will be
    // copied and replicated
    for(size_t i = 0; i < NETWORK_CAPACITY; ++i) {
      if(i != best_candidates[0] &&
	 i != best_candidates[1]) {
	delete networks[i];
	networks[i] = NULL;
	networks[i] = new NeuralNet(nets);
      }
    }
    nets[0] = NULL;
    nets[1] = NULL;
  }
  GeneticAlgorithm::generate_new_games();
  ++generation;
}

bool GeneticAlgorithm::play_game(NeuralNet * & curr,
				 Grid * & game, const size_t i) {
  short move = 0;
  std::ifstream infile("data.txt");
  if(infile) {
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
	break;
      }
      // place a new tile after the game itself has taken a new turn
      infile >> next_val;
      game -> place_tile(next_val);
    }
    // if the score attained from this algorithm is
    // better than the current highest score, replace it
    if(game -> get_score() > max_score) {
      max_score = game -> get_score();
      best_candidates[0] = i;
    }
  }
  infile.close();
}
// 
void GeneticAlgorithm::select_best_candidates(void) {
  unsigned long second_score = games[0] -> get_score();
  for(size_t i = 1; i < NETWORK_CAPACITY; ++i) {
    // to find the second fittest candidate in our set
    if(second_score < games[i] -> get_score() &&
       i != best_candidates[0]) {
      second_score = games[i] -> get_score();
      best_candidates[1] = i;
    }
  }
}

// serves as the real main function to the
// genetic algorithm.
bool GeneticAlgorithm::train(void) {
  typedef GeneticAlgorithm GA;
  while(!critereon(max_score)) {
    GA::new_generation();
    std::cerr << "created new generation on iteration " << generation << "\n";
    for(size_t i = 0; i < NETWORK_CAPACITY; ++i) {
      // each new neural network generated must play
      // their corresponding instance of a 2048 game
      GA::play_game(networks[i], games[i], i);
    }
    // the genetic algorithm then selects the best
    // candidates to be reproduced in the next generation
    GA::select_best_candidates();
    std::cerr << "iteration[" << generation << "]\t"
	      << "maximum value attained: " << std::setw(12)
	      << max_score << "\n\n";
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
