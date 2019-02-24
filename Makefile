#---------------------------------------------------
# makefile for the infection simulator
#---------------------------------------------------
CXX = g++
CXXFLAGS = -O2 -Wall
EXEC = infectsim
OBJ = main.o Board.o Human.o conio.o
SOLN = infectsim-soln.tar
DIST = infectsim-dist.tar

$(EXEC): $(OBJ)
	g++ -o $(EXEC) $(OBJ)

simulation: $(OBJ)

clean:
	rm -f $(EXEC) $(OBJ)
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
