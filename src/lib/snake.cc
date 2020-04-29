#include "snake.h"

///////////////////////////////////////////////
// Snake Helper Functions
//////////////////////////////////////////////
// initialize the snake
Snake::Snake(int h, int w) {
  _height = h; 
  _width = w; 
  _sl.clear(); 
  _dir = KEY_RIGHT; 
  int row = (int ) _height / 4; 
  int col = (int ) (_width / 4) + INIT_SNAKE_LEN;
  attron(COLOR_PAIR(snake_color)); // Change color
  for(int i = 0; i < INIT_SNAKE_LEN; i++) {
    move(row,col); 
    addch(SNAKE_CHAR); 
    auto p = std::make_pair(row,col); 
    _sl.push_back(p); 
    col--;
  }
  refresh(); 
}

// create food at some random point in the window
// displays this to the window
void Snake::CreateFood() {
  std::srand(std::time(nullptr)); 
  int col = std::rand() % (_width - 8) + 2; 
  int row = std::rand() % (_height - 8) + 2; 
  move(row,col); 
  attron(COLOR_PAIR(food_color)); // Change color
  addch(FOOD_CHAR); 
  _fl = std::make_pair(row,col); 
  refresh(); 
}

// helper function to add a segment to the front
void Snake::AddSegmentFront() {
  // add some snake length!!
  auto p = _sl.front(); 
  switch (GetSDir())
  { //row, h, 1st
    // col, w, 2nd
    case KEY_LEFT:
      /* code */
      p.second = std::max(0,p.second-1); 
      break;
    case KEY_RIGHT:
      /* code */
      p.second = std::min(p.second+1, _width); 
      break;
    case KEY_UP:
      /* code */
      p.first = std::max(0, p.first-1);
      break;
    case KEY_DOWN:
      /* code */
      p.first = std::min(p.first+1, _height); 
      break;
    default:
      break;
  }
  _sl.push_front(p); 

  // draw the updated position
  int row = _sl.front().first; 
  int col = _sl.front().second; 
  attron(COLOR_PAIR(snake_color));
  move(row,col); 
  addch(SNAKE_CHAR); 
  refresh(); 
}


/* called every time the snake moves to a new square to check for:
// Snake bit himself
// Snake hit wall
// Snake ate food 
  runtime: O(length)
   else the square is empty
*/
int Snake::CheckHeadPos() {
  auto head = _sl.front(); 
  if(head == _fl) {
    return food; 
  }
  else if(head.first < 1 || head.second < 1 || 
          head.first > _height-2 || head.second > _width-2) {
    return wall; 
  }
  auto itr = _sl.begin(); 
  itr++; // head
  itr++; // 3 is first part you can reach
  itr++; 
  for(itr; itr != _sl.end(); itr++) {
    if(*itr == head) {
      return snake; 
    }
  }
  return empty; 
}

// pop_back & push front depending on direction of travel
// displays this to the window
void Snake::MoveSnake() {
  int row = _sl.back().first; 
  int col = _sl.back().second; 
  move(row,col); 
  attron(COLOR_PAIR(blank_color)); // Change color
  addch(' '); 
  _sl.pop_back(); 
  AddSegmentFront(); 
}

// set the direction of the snake
void Snake::SetSDirection(int in_dir) {
  std::lock_guard<std::mutex> guard(dir_mutex);
  _dir = in_dir; 
}

// get curr dir
int Snake::GetSDir() {
  std::lock_guard<std::mutex> guard(dir_mutex);
  return _dir; 
}