#ifndef HUMAN_TEST_H
#define HUMAN_TEST_H

#include "../Human.h"
#include <iostream>

class MockBoard : public Board {
public:
  MockBoard() : Board(10, 10, 0) {}
  // We can override tryMove if needed, but for now base Board behavior is
  // conditional on Board state. Board::tryMove checks boundaries and other
  // humans.
};

namespace HumanTest {
void run(int &total, int &passed) {

  MockBoard *board = new MockBoard();

  // Test 1: Properties
  {
    total++;
    std::cout << "  [Human] Properties... ";
    Human h(1, 1, false, board);
    if (!h.isInfected() && !h.isDoctor() && !h.isCured()) {
      h.setInfected();
      if (h.isInfected()) {
        h.setCured();
        if (h.isCured() && !h.isInfected()) {
          std::cout << "PASSED" << std::endl;
          passed++;
        } else
          std::cout << "FAILED (Cured check)" << std::endl;
      } else
        std::cout << "FAILED (Infected check)" << std::endl;
    } else
      std::cout << "FAILED (Initial check)" << std::endl;
  }

  // Test 2: Location
  {
    total++;
    std::cout << "  [Human] Location... ";
    Human h(2, 3, false, board);
    int r, c;
    h.getLocation(r, c);
    if (r == 2 && c == 3) {
      h.setLocation(4, 5);
      h.getLocation(r, c);
      if (r == 4 && c == 5) {
        std::cout << "PASSED" << std::endl;
        passed++;
      } else
        std::cout << "FAILED (SetLocation)" << std::endl;
    } else {
      std::cout << "FAILED (GetLocation)" << std::endl;
    }
  }

  delete board;
}
} // namespace HumanTest

#endif
