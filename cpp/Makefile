# Configuration:
CC = g++
CFLAGS = -g -O2 -std=c++11

# This makefile compiles the project listed in the PROJ macro
SOURCES = Gomoku.cpp MinimaxPolicy.cpp RandomPolicy.cpp play.cpp TdLearner.cpp
OBJECTS = $(SOURCES:.cpp=.o)
TARGET = gomoku_ai

# Buid rule
$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

Gomoku.o : Gomoku.h Gomoku.cpp
	$(CC) $(CFLAGS) -c Gomoku.cpp
MinimaxPolicy.o : MinimaxPolicy.h MinimaxPolicy.cpp
	$(CC) $(CFLAGS) -c MinimaxPolicy.cpp
RandomPolicy.o : RandomPolicy.h RandomPolicy.cpp
	$(CC) $(CFLAGS) -c RandomPolicy.cpp
TdLearner.o : TdLearner.h TdLearner.cpp
	$(CC) $(CFLAGS) -c TdLearner.cpp
play.o : play.cpp
	$(CC) $(CFLAGS) -c play.cpp


# Phony means not a "real" target, it doesn't build anything
# The phony target "clean" is used to remove all compiled object files.
.PHONY: clean
clean:
	@rm -f $(TARGET) $(OBJECTS)

