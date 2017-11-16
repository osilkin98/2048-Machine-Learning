#include "grid.h"
#include <vector>
#include <climits>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <cctype>


bool Grid::play_game(void) {
  while(this -> has_merge()) {
    std::cout << "score: " << score << std::endl;
    this -> print(std::cout);
    std::cout << "swipe a direction: " << std::flush;
    char c;
    std::cin >> c;
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
    if(this -> take_turn(tolower(c))) {
      this -> place_tile();
    } else {
      std::cout << "there are no swipes that way" << std::endl;
    }
  }
  return true;
}




Grid::Grid(void) : board(4, std::vector<Tile*>(4)), active_tiles(0), score(0) {
  std::cerr << "Vector has successfully intialized: rows"
	    << board.size() << "\ncols: "
	    << board[0].size() << "\n";
  board_init();
}

void Grid::place_tile(void) {
  short counter = 0;
  for(size_t i = 0; i < board.size(); ++i) {
    for(size_t j = 0; j < board[i].size(); ++j) {
      if(board[i][j] == NULL) {
	++counter;
	if(board.size()*board.size() - active_tiles == counter) {
	  board[i][j] = new Tile;
	  ++(*board[i][j]);
	  ++active_tiles;
	  return;
	} else if(static_cast<double>(rand())/static_cast<double>(RAND_MAX)
	   <= (1/static_cast<double>(board.size()*board.size() -
				  active_tiles))) {
	  board[i][j] = new Tile;
	  ++(*board[i][j]);
	  ++active_tiles;
	  return;
	}
      }
    }
  }
}

void Grid::board_init(void) {
  srand(time(0));
  this -> place_tile();
  this -> place_tile();
  std::cerr << "the board has been successfullly initialized!\n";
}


bool Grid::take_turn(const char c) {
  switch(c) {
  case 'a':
    return this -> shift_left();
  case 'd':
    return this -> shift_right();
  case 's':
    return this -> shift_down();
  case 'w':
    return this -> shift_up();
  default:
    std::cerr << "somehow we ended up in the default case!\n";
    return false;
  }
}

Grid::Grid(const size_t board_size)
  : board(board_size, std::vector<Tile*>(board_size)),
    active_tiles(0), score(0) {
  std::cerr << "Vector has successfully initialized\n"
	    << "rows: " << board.size()
	    << "\ncols: " << board[0].size() << "\n";
  board_init();
}

Grid::~Grid(void) {
  for(size_t i = 0; i < board.size(); ++i) {
    for(size_t j = 0; j < board[i].size(); ++j) {
      //std::cerr << "deleting tile [" << i << "][" << j << "]...\n";
      delete board[i][j];
      active_tiles--;
      board[i][j] = NULL;
    }
  }
  std::cerr << "all the pointers on the board have been deallocated\n";
}
/*
unsigned long Grid::board_sum(void) const {
  unsigned long sum = 0;
  for(size_t i = 0; i < board.size(); ++i) {
    for(size_t j = 0; j < board[i].size(); ++j) {
      sum += board[i][j] -> get_value();
    }
  }
  return sum;
  }*/


void Grid::print(std::ostream & outs) const {
  std::ostringstream board_str;
  size_t width = 5;
  board_str << std::right;
  for(size_t row = 0; row < board.size(); ++row) {
    for(size_t col = 0; col < board[row].size(); ++col) {
      board_str << std::setw(width);
      if(!(board[row][col] != NULL)) {
	board_str << "-";
      } else {
	board_str << board[row][col] -> get_value();
      }
    }
    board_str << "\n";
  }
  outs << board_str.str() << std::endl;
}

void Grid::unmerge(void) {
  for(size_t row = 0; row < board.size(); ++row) {
    for(size_t col = 0; col < board[row].size(); ++col) {
      if(board[row][col] != NULL) {
	if(board[row][col] -> is_merged()) {	  
	   board[row][col] -> set_merged(false);
	}
      }
    }
  }
}

bool Grid::shift_right(void) {
  bool shifted = false;
  for(ssize_t i = 0; i < board.size(); ++i) {
    for(ssize_t j = board[i].size() - 2; j >= 0 ; --j) {
      if(board[i][j] == NULL) {
	continue;
      }
      ssize_t k = j + 1;
      
      bool whle = true;
      while(whle) {
	if(board[i][k] == NULL) {
	  shifted = true;
	  board[i][k] = board[i][k-1];
	  board[i][k-1] = NULL;
	} else if(board[i][k] -> get_value() ==
		  board[i][k-1] -> get_value() &&
		  !(board[i][k] -> is_merged()) &&
		  !(board[i][k-1] -> is_merged())) {
	  shifted = true;
	  delete board[i][k-1];
	  active_tiles--;
	  board[i][k-1] = NULL;
	  ++(*board[i][k]);
	  score += board[i][k] -> get_value();
	  board[i][k] -> set_merged(true);
	  whle = false;
	  break;
	}
	++k;
	whle = k < board[i].size() ? true : false;
      }
    }
  }
  this -> unmerge();
  return shifted;
}


bool Grid::shift_left(void) {
  bool shifted = false;
  //std::cerr << "board[0].size() = " << board[0].size() << "\n";
  for(ssize_t i = 0; i < board.size(); ++i) {
    for(ssize_t j = 1; j < board[i].size(); ++j) {
      if(board[i][j] == NULL) {
	continue;
      }
      ssize_t k = j - 1;
      /**
	 if the kth index is non-negative and either
	 the kth index is empty OR
	 the kth index has the same value as the k+1th index,
	 and neither have yet been merged
       **/
      bool whle = true;
      while(whle) {
	if(board[i][k] == NULL) {
	  shifted = true;
	  board[i][k] = board[i][k+1];
	  board[i][k+1] = NULL;
	} else if(board[i][k] -> get_value() ==
		  board[i][k+1] -> get_value() &&
		  !(board[i][k+1] -> is_merged()) &&
		  !(board[i][k] -> is_merged())) {
	  shifted = true;
	  delete board[i][k+1];
	  active_tiles--;
	  board[i][k+1] = NULL;
	  ++(*board[i][k]);
	  score += board[i][k] -> get_value();
	  board[i][k] -> set_merged(true);
	  whle = false;
	  break;
	}
	--k;
	whle = k >= 0 ? true : false;
      }
      //std::cerr << "about to do this -> print(std::cout)\n";
      //this -> print(std::cout);
      //std::cerr << "i: " << i << "\nj: " << j << "\n";
    }
  }
  //std::cerr << "about to reset merges\n";
  this -> unmerge();
  //return has_shift;
  return shifted;
}

bool Grid::shift_up(void) {
  bool shifted = false;
  for(ssize_t col = 0; col < board.size(); ++col) {
    for(ssize_t row = 1; row < board.size(); ++row) {
      if(board[row][col] == NULL) {
	continue;
      }
      ssize_t k = row - 1;
      bool whle = true;
      while(whle) {
	if(board[k][col] == NULL) {
	  shifted = true;
	  board[k][col] = board[k+1][col];
	  board[k+1][col] = NULL;
	} else if(*board[k][col] == *board[k+1][col] &&
		  !(board[k][col] -> is_merged()) &&
		  !(board[k+1][col] -> is_merged())) {
	  shifted = true;
	  ++(*board[k][col]);
	  score += board[k][col] -> get_value();
	  board[k][col] -> set_merged(true);
	  delete board[k+1][col];
	  active_tiles--;
	  board[k+1][col] = NULL;
	  break;
	}
	--k;
	whle = k >= 0;
      }
    }
  }
  this -> unmerge();
  return shifted;
}

bool Grid::shift_down(void) {
  bool shifted = false;
  for(ssize_t col = 0; col < board.size(); ++col) {
    for(ssize_t row = board.size() - 2; row >= 0; --row) {
      if(board[row][col] == NULL) {
	continue;
      }
      ssize_t k = row + 1;
      bool whle = true;
      while(whle) {
	if(board[k][col] == NULL) {
	  shifted = true;
	  board[k][col] = board[k-1][col];
	  board[k-1][col] = NULL;
	} else if( *board[k][col] == *board[k-1][col] &&
		   !(board[k][col] -> is_merged()) &&
		   !(board[k-1][col] -> is_merged())) {
	  shifted = true;
	  ++(*board[k][col]);
	  score += board[k][col] -> get_value();
	  board[k][col] -> set_merged(true);
	  delete board[k-1][col];
	  active_tiles--;
	  board[k-1][col] = NULL;
	  break;
	}
	++k;
	whle = k < board.size();
      }
    }
  }
  this -> unmerge();
  return shifted;
}

bool Grid::has_shift(void) const {
  if(active_tiles < 16) {
    return true;
  }
  return false;
}

bool Grid::check_right(size_t i, size_t j) const {
  bool x = false;
  if(j < board[i].size() - 1) {
    x = check_right(i, j+1);
  } else {
    std::cerr << "checking board[" << i << "][" << j << "] with "
	      << "board[" << i+1 << "][" << j<<  "]\n";
    return *board[i][j] == *board[i+1][j] &&
      !(board[i][j] -> is_merged()) &&
      !(board[i+1][j] -> is_merged());
  }
  std::cerr << "checking board[" << i << "][" << j << "] with "
	    << "board[" << i+1 << "][" << j << "] and board[" 
	    << i << "][" << j << "]\n";
  return x || (!(board[i][j] -> is_merged()) &&
	    ( !(board[i+1][j] -> is_merged()) ||
	      !(board[i][j+1] -> is_merged()) )) &&
	    (*board[i][j] == *board[i+1][j] ||
	     *board[i][j] == *board[i][j+1]);
}

bool Grid::check_down(size_t i, size_t j) const {
  bool x = false;
  if(i < board.size() - 2) {
    x = check_down(i+1, j);
  }
  x = x || check_right(i, j+1);
  std::cerr << "checking board[" << i << "][" << j << "] with "
	    << "board[" << i+1 << "][" << j << "]\n";
  return x || *board[i][j] == *board[i+1][j] &&
    !(board[i][j] -> is_merged()) &&
    !(board[i+1][j] -> is_merged());
}



bool Grid::valid_input(const char c) const {
  const char p[4] = {'w', 'a', 's', 'd'};
  for(size_t i = 0; i < 4; ++i) {
    if(tolower(c) == p[i]) {
      return true;
    }
  }
  return false;
}

bool Grid::has_merge(void) const {
  if(active_tiles < 16) {
    return true;
  } else {
    return check_down(0, 0);
  }
}


int main(void) {
  Grid gr;
  gr.play_game();
  return 0;
}
