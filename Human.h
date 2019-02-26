/**
 * Declaration of the Human class.
 *
 * @author Noah Lindsey
 * @date March 2016
 */

#include "Board.h"

#ifndef HUMAN_H
#define HUMAN_H

using namespace std;

/**
 * @class Human
 * @brief The Human class declaration.
 */
class Human {
    public:
        Human(int initRow, int initCol, bool initInfected, Board* thisBoard);
		virtual ~Human();
		virtual void move();
		virtual void draw();

		virtual void getLocation(int& row, int& col);
		virtual void setLocation(int row, int col);
		virtual void setInfected();
		virtual bool isInfected();
		virtual void setDoctor();
		virtual void setCured();
		virtual bool isCured();
		virtual bool isDoctor();

    protected:
        bool infected;
		bool doctor;
		bool cured;
		int row, col;
		int timeInfected;

		Board *board;   // Pointer to the board so the human can ask the board whether
						// the human can move to a given location on the board.
};

#endif
