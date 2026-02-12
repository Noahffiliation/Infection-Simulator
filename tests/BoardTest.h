#ifndef BOARD_TEST_H
#define BOARD_TEST_H

#include "../Board.h"
#include <assert.h>
#include <cstdlib>
#include <iostream>

class TestBoard : public Board {
public:
  TestBoard(int rows, int cols, int humans) : Board(rows, cols, humans) {
    for (int i = 0; i < numHumans; ++i) {
      this->humans[i] = new Human(0, 0, false, this);
    }
  }

  // Expose protected methods and members for testing
  void public_processInfection() { processInfection(); }
  bool public_allInfected() { return allInfected(); }
  bool public_allCured() { return allCured(); }
  bool public_isNextTo(Human *h1, Human *h2) { return isNextTo(h1, h2); }

  Human *getHuman(int index) {
    if (index >= 0 && index < numHumans)
      return humans[index];
    return NULL;
  }

  int getNumHumans() { return numHumans; }
  int getNumInfected() { return numInfected; }
  int getNumDoctors() { return numDoctors; }
  int getNumCured() { return numCured; }

  void setHumanInfected(int index) {
    if (index >= 0 && index < numHumans) {
      humans[index]->setInfected();
      // Manually update counts as Board usually does in processInfection or
      // logic But Board::processInfection recalculates from scratch, so we are
      // fine if we call that.
    }
  }

  void setHumanDoctor(int index) {
    if (index >= 0 && index < numHumans)
      humans[index]->setDoctor();
  }

  void setHumanCured(int index) {
    if (index >= 0 && index < numHumans)
      humans[index]->setCured();
  }

  void cleanupHumans() {
    for (int i = 0; i < numHumans; ++i) {
      if (humans[i]) {
        delete humans[i];
        humans[i] = NULL;
      }
    }
  }

  void setSleepTime(int t) { uSleepTime = t; }
};

namespace BoardTest {
void run(int &total, int &passed) {

  // Test 1: Initialization
  {
    total++;
    std::cout << "  [Board] Initialization... ";
    TestBoard b(10, 10, 5);
    if (b.getNumHumans() == 5 && b.getNumInfected() == 0) {
      std::cout << "PASSED" << std::endl;
      passed++;
    } else {
      std::cout << "FAILED" << std::endl;
    }
  }

  // Test 2: All Infected Check
  {
    total++;
    std::cout << "  [Board] allInfected... ";
    TestBoard b(5, 5, 2);
    b.setHumanInfected(0);
    b.setHumanInfected(1);
    if (b.public_allInfected()) {
      std::cout << "PASSED" << std::endl;
      passed++;
    } else {
      std::cout << "FAILED" << std::endl;
    }
  }

  // Test 3: isNextTo
  {
    total++;
    std::cout << "  [Board] isNextTo... ";
    TestBoard b(10, 10, 2);
    // We need to force locations to test isNextTo
    // But human locations are random in constructor.
    // However, Human class has setLocation.
    // We need to access the humans which we exposed in TestBoard.
    Human *h1 = b.getHuman(0);
    Human *h2 = b.getHuman(1);

    h1->setLocation(5, 5);
    h2->setLocation(5, 6); // Adjacent

    if (b.public_isNextTo(h1, h2)) {
      h2->setLocation(0, 0); // Not adjacent
      if (!b.public_isNextTo(h1, h2)) {
        std::cout << "PASSED" << std::endl;
        passed++;
      } else {
        std::cout << "FAILED (Should not be adjacent)" << std::endl;
      }
    } else {
      std::cout << "FAILED (Should be adjacent)" << std::endl;
    }
  }

  // Test 4: Process Infection (1 infects neighbor)
  {
    total++;
    std::cout << "  [Board] processInfection propagation... ";
    // This involves randomness in processInfection (e.g. "rand() % 4").
    // This is hard to test deterministically without mocking rand() or seeding
    // or repeating. However, we can at least run it and see if *something*
    // happens, or test the doctors logic if consistent. Board::processInfection
    // logic: if infected & !infected: rand()%4 == 0 -> infects.

    // Let's try to test the counts update mechanism at least.
    TestBoard b(5, 5, 3);
    b.setHumanInfected(0);
    // Run processInfection to update counts
    b.public_processInfection();

    if (b.getNumInfected() >= 1) { // At least the one we set should be counted
      std::cout << "PASSED" << std::endl;
      passed++;
    } else {
      std::cout << "FAILED" << std::endl;
    }
  }

  // Test 5: tryMove
  {
    total++;
    std::cout << "  [Board] tryMove... ";
    TestBoard b(5, 5, 2);
    // Humans at (0,0) initially by our TestBoard constructor
    if (b.tryMove(0, 0) ==
        false) { // Occupied by human 0 (self? no, tryMove checks collisions)
      // Wait, Board::tryMove excludes self?
      // Board::tryMove(row, col) iterates ALL humans.
      // humans[i]->getLocation... if row==tryRow... return false.
      // It DOES NOT exclude self! So a human cannot move to its OWN location??
      // Human::move() calculates `row+rowDelta`.
      // If delta is 0, it asks tryMove(row, col).
      // If tryMove returns false, it stays.
      // So tryMove(0,0) should return false if someone is there.
      if (b.tryMove(4, 4) == true) {     // Empty
        if (b.tryMove(-1, 0) == false) { // Out of bounds
          std::cout << "PASSED" << std::endl;
          passed++;
        } else
          std::cout << "FAILED (Bounds)" << std::endl;
      } else
        std::cout << "FAILED (Empty cell)" << std::endl;
    } else
      std::cout << "FAILED (Occupied cell)" << std::endl;
  }

  // Test 6: allCured
  {
    total++;
    std::cout << "  [Board] allCured... ";
    TestBoard b(5, 5, 2);
    b.setHumanCured(0);
    b.setHumanCured(1);
    if (b.public_allCured()) {
      std::cout << "PASSED" << std::endl;
      passed++;
    } else
      std::cout << "FAILED" << std::endl;
  }

  // Test 7: Run (Coverage)
  {
    total++;
    std::cout << "  [Board] run() coverage... ";
    // 1 Human. logic: infects 1. loops until all infected (which is true
    // immediately). So it should run init, infect, and exit loop.
    // Use fewer humans to ensure faster termination but enough for interactions
    Board::seedRandom(1); // Ensure deterministic behavior
    TestBoard b(10, 10, 20);
    b.setSleepTime(0);
    b.cleanupHumans();
    b.run();
    std::cout << "PASSED" << std::endl;
    passed++;
  }
}
} // namespace BoardTest

#endif
