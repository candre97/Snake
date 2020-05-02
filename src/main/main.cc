#include "src/lib/game.h"
#include <chrono>
#include <ctime>
#include <iomanip> // put_time
#include <iostream>
#include <ncurses.h>
#include <sstream> // stringstream
#include <unistd.h>
#include <thread> 
#include <mutex>

//////////////////////////////////////
// Function Prototypes
//////////////////////////////////////
// thread which updates the frame every update_freq ms
void UpdateSnake(Game* g, int update_freq);
// thread for receiving user input
void GetDir(Game* g);
// get user input to set difficulty
int GetDifficulty(); 


///////////////////////
// MAIN 
///////////////////////
int main() {
  int update_freqs[3] = {75, 60, 45};  // miliseconds
  int difficulty = 0;
  int high_score = 0; 
  char again = 'n'; 

  do {
    if(again == 'y') {
      std::cout << "*****************************************" << std::endl; 
      std::cout << "The High Score to Beat: " << high_score << std::endl; 
    }
    else {
      std::cout << "Welcome to the retro C++ Snake Game" << std::endl << std::endl; 
      std::this_thread::sleep_for(std::chrono::milliseconds(1500));
      std::cout << "For best results make your Terminal FULL SCREEN!" << std::endl << std::endl; 
      std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    }

    // Get difficulty
    int difficulty = GetDifficulty(); 
    
    // initialize game board
    Game* g = new Game();

    // sleep for 1 second, then start the game
    std::this_thread::sleep_for(std::chrono::seconds(1)); 
    
    // start threads
    std::thread m(UpdateSnake, std::ref(g), update_freqs[difficulty-1]); 
    m.detach(); 
    std::thread in(GetDir, std::ref(g));
    in.join();  // main thread stops here until input thread is done... 

    // display game results
    g->NewHighScore(high_score);  // only does something if there is a new high score
    g->DisplayScore();            // display score of current round and cause of death

    g->~Game(); // destructor... game over!!

    // play again?
    std::cout << std::endl << "Current High Score: " << high_score << std::endl;; 
    std::cout << "Want to play again? [y/n]: ";
    std::cin >> again;  
  } while(again == 'y'); 

  std::cout << std::endl << "Thanks for playing the C++ Snake Game!" << std::endl; 
  std::cout << "High Score for the Day: " << high_score << std::endl; 
  std::cout << "Goodbye!" << std::endl << std::endl; 

  return EXIT_SUCCESS;
}


// thread which updates the frame every update_freq ms
void UpdateSnake(Game* g, int update_freq) {
  while(!g->GetGameOver()) {
    g->NextFrame(); 
    // cap the speed, though getting this far seems impossible anyways
    std::this_thread::sleep_for(std::chrono::milliseconds(std::max(update_freq - (2*g->GetScore()), 20) )); 
  }
}

// thread for receiving user input
void GetDir(Game* g) {
  while(!g->GetGameOver()) {
    int in = getch(); 
    switch(in) {
      case KEY_UP:
        if(g->GetDir() != KEY_DOWN) {
          g->SetDir(KEY_UP); 
        }
        break;
      case KEY_DOWN:
        if(g->GetDir()  != KEY_UP) {
          g->SetDir(KEY_DOWN); 
       } 
        break; 
      case KEY_LEFT:
        if(g->GetDir()  != KEY_RIGHT) {
          g->SetDir(KEY_LEFT); 
        }
        break;
      case KEY_RIGHT:
        if(g->GetDir()  != KEY_LEFT) {
          g->SetDir(KEY_RIGHT); 
        }
        break;
    }
  }
}

// get user input to set difficulty
int GetDifficulty() {
  int difficulty = 0; 
  do {
    std::cout << "Please select from the following levels of difficulty: " << std::endl;
    std::cout << "\t1) Novice" << std::endl; 
    std::cout << "\t2) Intermediate" << std::endl; 
    std::cout << "\t3) Snake Charmer" << std::endl; 
    std::cout << "Enter a number (1,2,3) to select your level of difficulty: " << std::endl; 
    std::cout << "> "; 
    std::cin >> difficulty;
    if(difficulty > 3 || difficulty < 1) {
      std::cout << "Invalid Selection" << std::endl << std::endl; 
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      std::cout << "Please select a valid option... " << std::endl; 
    }
  } while (difficulty > 3 || difficulty < 1);
  return difficulty; 
}

