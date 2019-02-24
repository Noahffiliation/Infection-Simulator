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

	// "Setters" and "getters"
	virtual void getLocation(int& row, int& col);
	virtual void setLocation(int row, int col);
	virtual void setInfected();
	virtual bool isInfected();
	virtual void setDoctor();
	virtual void setCured();
	virtual bool isCured();
	virtual bool isDoctor();

    protected:
        bool infected;     // Track whether or not this human is infected.
	bool doctor;	   // Track whether or not this human is a doctor.
	bool cured;	   // Track whther or not this human is cured.
	int row, col;      // The row and column where this human is on the board.
	int timeInfected;  // Tracks how long human has been infected

	Board *board;      // Pointer to the board so the human can ask the board whether
	                   // the human can move to a given location on the board.
};

#endif // HUMAN_H
