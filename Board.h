#ifndef BOARD_H
#define BOARD_H

/**
 * @file Board.h
 * @brief the Board class declaration file
 *
 * @author Noah Lindsey
 * @date March 2016
 */

//----------------------------------------------------
// "forward" declaration of Board. Tell the compiler that this will be
// defined properly further "forward" in the program. This is needed because
// both classes reference each other. Otherwise, when include "Human.h" and 
// the compiler finds a reference to Board, it will complain.
//----------------------------------------------------
class Board;

#include "Human.h"

using namespace std;

/**
 * @class Board
 * @brief The Board class declaration.
 */
class Board {
  public:
      Board(int numRows, int numCols, int numHumans);
      ~Board();
      void run();
      bool tryMove(int row, int col);
      static const int MAX_HUMAN_COUNT = 100;

  protected:
      void processInfection();
      bool allInfected();
      bool allCured();
      bool isNextTo(Human* h1, Human* h2);

      Human* humans[MAX_HUMAN_COUNT];
      int numHumans;
      int numInfected;
      int numCured;
      int numDoctors;
      int currentTime;
      int numRows;
      int numCols;
      int uSleepTime;
};

#endif
