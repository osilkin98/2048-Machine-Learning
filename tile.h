#ifndef TILE_H
#define TILE_H
#include <iostream> // this is required for ssize_t

class Tile {
 private:
  unsigned long value;
  bool merged;
 public:
  Tile(void); // default constructor will not be used.
  
  Tile(const Tile & other); // copy ctor


  /*** MUTATORS ***/
  
  Tile& operator++(void);

  bool set_merged(bool val);
  
  //void set_x(const size_t new_x);
  //void set_y(const size_t new_y);
  //void translate_x(const ssize_t dx);
  //void translate_y(const ssize_t dy);

  /** ACCESSORS ***/
  unsigned long get_value(void) const { return value; }
  bool is_merged(void) const { return merged; }
  //const size_t get_x(void) const { return x; }
  //const size_t get_y(void) const { return y; }
  //const bool is_used(void) const { return is_null; }
  
  bool operator==(const Tile & other) const {
    return value == other.value;
  }
  
  //Tile& operator++(void);

  bool operator<(const unsigned long comp) const {
    return value < comp;
  }
  void print(std::ostream outs) const {
    outs << "Value: " << value; 
  }
  void increment_value(void);
};

#endif
