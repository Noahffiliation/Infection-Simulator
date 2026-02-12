#---------------------------------------------------
# makefile for the infection simulator
#---------------------------------------------------
CXX = g++
CXXFLAGS = -O2 -Wall -fprofile-arcs -ftest-coverage
EXEC = infectsim
OBJ = main.o Board.o Human.o conio.o
TEST_OBJ = Board.o Human.o conio.o tests/test_main.o
SOLN = infectsim-soln.tar
DIST = infectsim-dist.tar

$(EXEC): $(OBJ)
	g++ $(CXXFLAGS) -o $(EXEC) $(OBJ) -lgcov

simulation: $(OBJ)

clean:
	rm -f $(EXEC) $(OBJ) run_tests $(TEST_OBJ) *.gcno *.gcda *.gcov *.info tests/*.gcno tests/*.gcda tests/*.gcov tests/*.info

tests: $(TEST_OBJ)
	g++ -o run_tests $(TEST_OBJ) -lgcov --coverage

coverage: tests
	./run_tests
	lcov --capture --directory . --output-file coverage.info
	lcov --remove coverage.info '/usr/*' --output-file coverage.info
	lcov --list coverage.info
soln:
	tar cvf $(SOLN) Makefile *.cpp *.h
	@echo "The tarfile is '$(SOLN)'."
dist:
	tar cvf $(DIST) Makefile *.cpp *.h
	@echo "The tarfile is '$(DIST)'."

Board.o: Board.h Human.h conio.h
Human.o: Human.h Board.h conio.h
conio.o: conio.h
main.o: Board.h Human.h
