#ifndef GRID_H
#define GRID_H
#include <vector>
#include <iostream>
#include "tile.h"

class Grid {
 private:
  std::vector< std::vector<Tile*> > board;
  unsigned long score;
  short active_tiles;
  bool is_init;
  
 public:
  /*** constructors ***/
  Grid(void); // default ctor
  Grid(const size_t board_size); // specific ctor
  ~Grid(void);

  /*** initialization function ***/
  void board_init(void);

  /*******************************/
  /******** MAIN FUNCTION ********/
  /*******************************/

  bool play_game(void);

  unsigned long get_value_at(size_t i, size_t j) const {
    if(board[i][j] == NULL) { return 0; }
    return board[i][j] -> get_value();
  }

  
  // accessor functions
  bool is_empty(size_t x, size_t y) const {
    return board[x][y] != NULL;
  }

  
  
  void print(std::ostream & outs) const;

  unsigned long get_score(void) const { return score; }
  
  // mutator functions 
  //bool shift_elem(ssize_t dx, ssize_t dy);

  void unmerge(void);
  bool take_turn(const char);
  void place_tile(void);
  size_t board_size(void) const {
    return board.size();
  }
  bool shift_left(void);
  bool shift_right(void);
  bool shift_up(void);
  bool shift_down(void);

 
  bool valid_input(const char c) const;
  // for the has_shift function 
  bool check_right(size_t i, size_t j) const;
  bool check_down(size_t i, size_t j) const;
  
  bool has_merge(void) const;
  bool has_shift(void) const;
  
};

#endif
