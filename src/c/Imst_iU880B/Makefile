# Makefile to build the LoRa sender
# see: http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/
CC=gcc
CFLAGS=-I.
CXXFLAGS=-std=c++11
BIN=LoRaSender

SRC=$(wildcard *.cpp)
OBJ=$(SRC:%.cpp=%.o)

all: $(OBJ)
	$(CC) ${CFLAGS} -o $(BIN) $^

%.o: %.c
	$(CC) $@ -c $<

clean:
	rm -vf *.o
	rm -v $(BIN)
