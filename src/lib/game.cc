#include "game.h"

// constructor to create a game. 
// does all Ncurses initialization
// initializes all member variables
// calls the snake constructor
Game::Game() {
  // screen initialization
  initscr();
  cbreak(); 
  noecho(); // suppress automatic echo of typed input
  keypad(stdscr, TRUE); // enable input of backspace, delete, arrow keys
  curs_set(0); // make cursor invisible

  // color initialization
  start_color(); // start color
  init_pair(snake_color, COLOR_YELLOW, COLOR_GREEN);
  init_pair(food_color, COLOR_RED, COLOR_BLACK);
  init_pair(blank_color, COLOR_BLACK, COLOR_BLACK);
  init_pair(b_and_w, COLOR_WHITE, COLOR_BLACK);
  if (has_colors() == FALSE) {
    endwin();
    std::cout << "Your terminal does not support color" << std::endl; 
    exit(1);
  }
  // create box outline of playing area
  clear(); 
  box(stdscr, 0 , 0); 
  refresh();
  int h, w;
  getmaxyx(stdscr, h, w);

  _width = w;   // of window
  _height = h;  // of window
  _score = 0;   // score
  _game_over = 0; 
  _s = new Snake(h,w);         // snake in the game
  _s->CreateFood(); 
  refresh(); 
}

// destructor for the game
Game::~Game() {
  delete _s;
  clear(); 
  endwin();
}

void Game::PressAnyKey() {
  attron(COLOR_PAIR(b_and_w));
  std::string quit = "Press any key"; 
  mvwprintw(stdscr, _height/2, _width/2-6, "%s", quit.c_str());
  refresh(); 
  getch(); 
  clear(); 
}

// Display the final score, called at the end of the game
void Game::DisplayScore() {
  attron(COLOR_PAIR(b_and_w));
  clear(); 
  std::string cod = "Cause of Death: "; 
  switch (_game_over)
  {
    case snake:
      cod += "Bit Yourself"; 
      break;
    case wall:
      cod += "Hit Wall"; 
      break;
    default:
      cod += "ERROR"; 
      break;
  }
  mvwprintw(stdscr, _height/2 - 8, _width/2-10, "%s", cod.c_str());
  std::string score = "Your Score: " + std::to_string(_score); 
  mvwprintw(stdscr, _height/2 - 3, _width/2-5, "%s", score.c_str());
  std::string quit = "Press any key"; 
  mvwprintw(stdscr, _height/2 + 3, _width/2-6, "%s", quit.c_str());
  getch(); 
}

// Displays if there is a new high score at end of game
void Game::NewHighScore(int& high_score) {
  // clear screen
  if(_score > high_score) {
    attron(COLOR_PAIR(b_and_w));
    clear(); 
    std::string score = "NEW HIGH SCORE: " + std::to_string(_score); 
    mvwprintw(stdscr, _height/2, _width/2-5, "%s", score.c_str());
    high_score = _score; 
    getch(); 
  }
}

// called at specified intervals depending on difficulty
// calls the snake's MoveSnake and CheckHeadPos Functions
void Game::NextFrame() {
  _s->MoveSnake(); 

  int res = _s->CheckHeadPos(); 
  if(res == wall) {
    _game_over = wall; 
    PressAnyKey(); 
  }
  else if(res == snake) {
    _game_over = snake; 
    PressAnyKey(); 
  }
  else if(res == food) {
    _score++; 
    _s->CreateFood(); 
    _s->AddSegmentFront(); 
    _s->AddSegmentFront(); 
  } 
  // else -- empty!
}

// returns the Snake of the game
Snake* Game::GetSnake() {
  return _s; 
}

// returns state of the game
int Game::GetGameOver() {
  return _game_over; 
}

// returns current Dir
int Game::GetDir() {
  return _s->GetSDir(); 
}

// sets the new Direction
void Game::SetDir(int dir) {
  _s->SetSDirection(dir); 
} 

int Game::GetScore() {
  return _score; 
}