OBJ := GoBangGame
CC := g++
CCFLAGS := -Wall -std=c++11
SRC := GoBangBoard.hpp \
	GoBangBoard.cpp \
	Player.hpp \
	Player.cpp \
	GameControl.hpp \
	GameControl.cpp \
	maintest.cpp


$(OBJ):$(SRC)
	$(CC) $(CCFLAGS) $(SRC) -o $@ 



.PHONY:clean
clean:
	-rm *~
	-rm $(OBJ)
	-rm #*
