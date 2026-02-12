#include "BoardTest.h"
#include "HumanTest.h"
#include <iostream>


int main() {
  int total = 0;
  int passed = 0;

  std::cout << "========================================" << std::endl;
  std::cout << "Running Infection Simulator Tests" << std::endl;
  std::cout << "========================================" << std::endl;

  std::cout << "Running Board Tests..." << std::endl;
  BoardTest::run(total, passed);

  std::cout << "Running Human Tests..." << std::endl;
  HumanTest::run(total, passed);

  std::cout << "========================================" << std::endl;
  std::cout << "Total Tests: " << total << std::endl;
  std::cout << "Passed: " << passed << std::endl;

  if (total == passed) {
    std::cout << "ALL TESTS PASSED" << std::endl;
    return 0;
  } else {
    std::cout << "SOME TESTS FAILED" << std::endl;
    return 1;
  }
}
