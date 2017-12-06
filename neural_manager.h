#ifndef NEURAL_MANAGER_H
#define NEURAL_MANAGER_H
#include "grid.h"
#include "neuralnet.h"
#include <vector>
#include <iostream>
#include <fstream>

/* Genetic Algorithm should:
 * Create in parallel, N number of neural networks
 * as well as their corresponding games.
 * each neural network should then play the game
 * until a condition is reached where the neural
 * network can no longer move and there is no
 * difference in score from the last round to the 
 * current round. The defined fitness function
 * should be the current score over the
 * highest score attainded.
 * At the end of each iteration, the two networks
 * With the highest fitness scores will be 
 * chosen as the parents and will be combined,
 * randomly such that there will be an even chance
 * of getting either parent's genes, as well as
 * the off chance of mutating.
 * With these new off-spring, we repeat the 
 * iteration.
 *
 * while( critereon is not met) :
 *   recombine neural networks
 *   mutate neural networks
 *   calculate fitness value
 *   check critereon
 * dump neural network values
 */




class GeneticAlgorithm {
 private:
  std::vector<NeuralNet*> networks;
  std::vector<Grid*> games;
  std::vector<size_t> best_candidates;
  unsigned long max_score, generation;
 public:
  GeneticAlgorithm(void);
  ~GeneticAlgorithm(void);
  void generate_new_games(void);
  void select_best_candidates(void);
  bool critereon(unsigned long score) const {
    return score > 32678;
  }

  void new_generation(void);

  bool play_game(NeuralNet * & test_net,
		 Grid * & game, const size_t i);
  
  bool train(void);
};

#endif
