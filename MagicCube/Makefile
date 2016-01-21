CC := g++ -std=c++11
CCFLAGS := -g -Wall
SRC := magiccube.hpp \
	magiccube.cpp \

OBJ := cube

$(OBJ):$(SRC)
	$(CC) $(CCFLAGS) -o $@ $(SRC)



.PHONY:clean

clean:
	-rm $(OBJ) *~

.PHONY:check-syntax
check-syntax:
	$(CC) $(CCFLAGS) -Wall -Wextra -fsyntax-only $(SRC)
