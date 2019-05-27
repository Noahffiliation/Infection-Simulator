/**
 * @file Human.cpp
 * @brief The Human class implementation file.
 *
 * @author Noah Lindsey
 * @date March 2016
 */

#include <cstdlib>
#include <iostream>

#include "Human.h"
#include "conio.h"

using namespace std;

/**
 * @brief The Human class constructor.
 * This function initializes the row, col, infected, and board variables.
 *
 * @param initRow the initial human row location.
 * @param initCol the initial human column location.
 * @param initInfected whether the human is initially infected.
 * @param theBoard a pointer to the board (used to ask board whether a proposed move is ok).
 */
Human::Human(int initRow, int initCol, bool initInfected, Board *theBoard) {
    row = initRow;
    col = initCol;
    infected = initInfected;
    board = theBoard;
}

/**
 * @brief The Human class destructor.
 * The Human class destructor does nothing (so far), but is here as a placeholder to remind
 * you that it is a good idea for classes to have destructors, even if you can't think of 
 * work for destructor at this point.
 */
Human::~Human() {
    // Nothing to do
}

/**
 * @brief Have the human try to move.
 * To know whether it is ok to move to some position (r,c), ask the board
 * whether the position is ok. E.g., "if( board->tryMove(r,c) ) ..."
 * If the move is ok, then update the human's row and column to reflect the move.
 */
void Human::move() {
    // Generate a +/- 2 row and column delta.
    int rowDelta = rand() % 5 - 2, colDelta = rand() % 5 - 2;

    // Ask the board whether you
    if (board->tryMove(row + rowDelta, col + colDelta)) {
        row+=rowDelta;
        col+=colDelta;
    }
}

/**
 * @brief Get the human's current row/col location.
 * Returns the human's current row/column location via the reference parameters.
 * @param[out] currentRow the human's current row  
 * @param[out] currentCol the human's current column
 */
void Human::getLocation(int& currentRow, int& currentCol) {
    currentRow = row;
    currentCol = col;
}

/**
 * @brief Set the human's row/col location.
 * Sets the human's current row/column location to the parameter values.
 * @param[in] newRow the human's new row location
 * @param[in] newCol the human's new column location
 */
void Human::setLocation(int newRow, int newCol) {
    row = newRow;
    col = newCol;
}

/**
 * @brief Sets this human to be infected.
 * Sets this human object's state to infected.
 */
void Human::setInfected() {
    if(!this->isCured()) {
        infected = true;
        doctor = false;
        cured = false;
    }
}

/**
 * @brief reports whether this human is infected.
 * @return whether this human object is infected.
 */
bool Human::isInfected() {
    return infected;
}

/**
 * @brief Draws the human.
 * Draws the human at the current row/col location on the screen.
 * Remember that the first conio row=1, and first conio col=1.
 */
void Human::draw() {
    cout << conio::gotoRowCol(row+1,col+1);
    if (infected) {
        cout << conio::bgColor(conio::LIGHT_RED);
    } else if (doctor) {
	    cout << conio::bgColor(conio::LIGHT_BLUE);
    } else if (cured) {
	    cout << conio::bgColor(conio::YELLOW);
    } else {
        cout << conio::bgColor(conio::LIGHT_GREEN);
    }
    cout << '@' << conio::resetAll() << flush;
}

/**
 * @brief Sets human as a Doctor
 * Sets human object to a doctor.
 */
void Human::setDoctor() {
    infected = false;
    doctor = true;
    cured = true;
}

/** 
 * @brief Sets human as cured.
 * Sets human object as cured.
 */
void Human::setCured() {
    infected = false;
    cured = true;
}

/**
 * @brief reports whether this human is cured.
 * @return whether this human object is cured.
 */
bool Human::isCured() {
    return cured;
}

/**
 * @brief reports whether this human is a doctor.
 * @return whether this human object is a doctor.
 */
bool Human::isDoctor() {
    return doctor;
}
