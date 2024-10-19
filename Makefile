CC= g++
CXXFLAGS=-std=c++11 -Wall
LDFLAGS=-lpthread
EXEC=carrerasThreadsFinal

SRC=carreraThreadsFinal.cpp
all=${EXEC}

${EXEC}: carreraThreadsFinal.cpp
        ${CC} ${CXXFLAGS} -o ${EXEC} ${SRC}
clean:
        rm -rf *.o
