#include "grid.h"
#include "neuralnet.h"
#include "neural_manager.h"
#include <vector>

#define NETWORK_CAPACITY 8

GeneticAlgorithm::GeneticAlgorithm(void) :
  networks(NETWORK_CAPACITY), games(NETWORK_CAPACITY),
  max_score(0), best_candidate(NETWORK_CAPACITY), generation(0) {
  for(short i = 0; i < NETWORK_CAPACITY; ++i) {
    networks[i] = new NeuralNet;
    games[i] = new Grid;
  }
}

GeneticAlgorithm::~GeneticAlgorithm(void) {
  for(size_t i = 0; i < NETWORK_CAPACITY; ++i) {
    delete networks[i];
    networks[i] = NULL;
    delete games[i];
    games[i] = NULL;
  }
}

void GeneticAlgorithm::new_generation(void) {
  // for(unsigned short i = 0; i < NETWORK_CAPACITY; ++i) {
  //}
}



bool GeneticAlgorithm::train(void) {
  while(!critereon(max_score)) {
    new_generation();
    
  }
}

int main() {
  GeneticAlgorithm ga;
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
