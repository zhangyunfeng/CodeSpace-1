CC := g++

CCFLAGS := -g -Wall -std=c++11

INCPATH := -I./ \
	-I./ThirdLib/tinyxml \

LIBPATH := -L./ThirdLib/tinyxml \


#LIBS := -ltinyxml

Obj := CountIds
Main := ./main.cpp


SRC := ./CountId.hpp \
	./CountId.cpp \
	./main.cpp \
	./ThirdLib/tinyxml/tinyxml.cpp \
	./ThirdLib/tinyxml/tinyxmlparser.cpp \
	./ThirdLib/tinyxml/tinyxmlerror.cpp \
	./ThirdLib/tinyxml/tinystr.cpp

$(Obj):
	$(CC) $(CCFLAGS) $(SRC) -o $@ $(INCPATH) $(LIBPATH) $(LIBS)


.PHONY:clean

clean:
	-rm $(Obj)
	-rm *.o
	-rm *~
