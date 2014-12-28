CC := g++ -std=c++11
OBJ := cache_fifo
CCFLAGS := -Wall 
SRC := ./cache_link.h \
	./cache_link.cpp \
	./Test_Main.cpp


$(OBJ):$(SRC)
	$(CC) -o $(OBJ) $(CCFLAGS) $(SRC)

.PHONY:clean
clean:
	rm *~ $(OBJ)
