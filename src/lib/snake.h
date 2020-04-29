#ifndef SNAKE_H
#define SNAKE_H

#include <map>
#include <ncurses.h>
#include <string>
#include <unistd.h>
#include <list> 
#include <cstdlib>
#include <chrono> 
#include <mutex> 

#define INIT_SNAKE_LEN   5
#define FOOD_CHAR        ACS_CKBOARD
#define SNAKE_CHAR       ACS_DIAMOND

// keep track of colors
// for changing colors before drawing on terminal
enum colors {
  snake_color = 1,
  food_color = 2, 
  blank_color = 3,
  b_and_w = 4
};

// whats in this square?
// used by CheckHeadPos()
enum square {
  empty = 0,
  food = 1,
  wall = 2,
  snake = 3
};

class Snake {
public:
  // constructor that draws the snake in starting position
  Snake(int h, int w);  

  // create food at some random point in the window
  // displays this to the window
  void CreateFood();

  /* called every time the snake moves to a new square to check for:
  // 1. Snake bit himself
  // 2. Snake hit wall
  // 3. Snake ate food */
  // Runtime: O(length)
  int CheckHeadPos(); // check where the head is now

  // pop_back & push front depending on direction of travel
  // displays this to the window
  void MoveSnake(); 

  // Adds a segment in front of the snake
  void AddSegmentFront(); 

  // set the direction of the snake
  void SetSDirection(int in_dir); 

  // get curr dir
  int GetSDir(); 

private: 
  std::list<std::pair<int,int>> _sl;  // snake location
  std::pair<int,int> _fl;             // food location  
  int _width = 0;   // of window
  int _height = 0;  // of window
  int _dir = KEY_RIGHT;     // direction of travel
  std::mutex dir_mutex; 
}; 

#endif