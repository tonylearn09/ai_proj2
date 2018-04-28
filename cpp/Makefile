# Configuration:
CC = g++
CFLAGS = -g -O2 -std=c++11

# This makefile compiles the project listed in the PROJ macro
SOURCES = Gomoku.cpp MinimaxPolicy.cpp RandomPolicy.cpp play.cpp
OBJECTS = $(SOURCES:.c=.o)
TARGET = gomoku_ai

# Buid rule
$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

Gomoku.o : Gomoku.h
	$(CC) $(CFLAGS) -c Gomoku.cpp
MinimaxPolicy.o : MinimaxPolicy.h
	$(CC) $(CFLAGS) -c MinimaxPolicy.cpp
RandomPolicy.o : RandomPolicy.h
	$(CC) $(CFLAGS) -c RandomPolicy.cpp
play.o :
	$(CC) $(CFLAGS) -c play.cpp


# Phony means not a "real" target, it doesn't build anything
# The phony target "clean" is used to remove all compiled object files.
.PHONY: clean
clean:
	@rm -f $(TARGET) $(OBJECTS) core

