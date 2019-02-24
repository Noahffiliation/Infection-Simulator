/**
 * @file main.cpp
 * @brief Contains the main function that starts the infection simulation.
 *
 * @author Noah Lindsey
 * @date March 2016
 **/

#include <iostream>
#include <cstdlib>
#include <string>

// Board.h needs to be included here because we create a Board
// object below.
#include "Board.h"

using namespace std;

/**
 * @fn main()
 * @brief main function that starts the simulation running
 * The main function does the following:
 * (1) seeds the random number generator
 * (2) creates a board object that is 20 rows, 80 columns, 70 humans
 * (3) starts the simulation running by calling the board's run function.
 **/
int main() {
    srandom( time(NULL) );

    cout << "This infection simulation puts one doctor against one infected. The doctor must cure all the humans before he falls to the infection." << endl;
    cout << "Type RUN to start simulation:" << endl;
    string x;
    cin >> x;

    if (x == "RUN") {
        //Board board(20, 80, 70);
        Board board(30, 90, 80);
        board.run();
    }

    return 0;
}
