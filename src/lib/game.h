#ifndef GAME_H
#define GAME_H

#include <map>
#include <ncurses.h>
#include <string>
#include <unistd.h>
#include <list> 
#include <cstdlib>
#include <chrono> 
#include "snake.h"
#include <iostream> 

class Game {
public:

  Game();  // constructor to create a game. will call the snake constructor

  ~Game(); 

  // displays after a loss
  void PressAnyKey(); 

  // Display the final score, called at the end of the game
  void DisplayScore(); 

  // Displays if there is a new high score at end of game
  void NewHighScore(int& high_score); 

  // called at specified intervals depending on difficulty
  // calls the snake's MoveSnake and CheckHeadPos Functions
  void NextFrame(); 

  // returns the Snake of the game
  Snake* GetSnake(); 

  // returns Game Over State of the game
  int GetGameOver(); 

  // returns current Dir
  int GetDir(); 

  // sets the new Direction
  void SetDir(int dir); 

  // get _score
  int GetScore(); 

private: 
  int _width;   // of window
  int _height;  // of window
  int _score;   // score
  int _game_over; // whether game is over, reason for loss
  Snake* _s;         // snake in the game
}; 

#endif