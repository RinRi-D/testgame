CXX = g++
CXXFLAGS = -g -Wall -std=c++17
LDFLAGS = -lpthread

SRC = main.cpp object.cpp world.cpp
OBJ = ${SRC:.cpp=.o}

all: main

.o: ${OBJ}
	${CXX} -c ${CXXFLAGS} $<

main: ${OBJ}
	${CXX} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f main ${OBJ}