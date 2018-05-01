# Configuration:
CC = g++
CFLAGS = -g -O2 -std=c++11

SOURCES = Move.cpp State.cpp Field.cpp Evaluater.cpp ThreatPattern.cpp \
		  ThreatUtils.cpp Gomoku.cpp NegamaxPlayer.cpp RandomPolicy.cpp play.cpp
OBJECTS = Move.o State.o Field.o Evaluater.o ThreatPattern.o \
		  ThreatUtils.o Gomoku.o NegamaxPlayer.o RandomPolicy.o play.o
TARGET = play

# Buid rule
all : $(TARGET)
$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

Move.o : Move.h Move.cpp
	$(CC) $(CFLAGS) -c Move.cpp
State.o : State.h State.cpp
	$(CC) $(CFLAGS) -c State.cpp
Field.o : Field.h Field.cpp
	$(CC) $(CFLAGS) -c Field.cpp
Evaluater.o : Evaluater.h Evaluater.cpp
	$(CC) $(CFLAGS) -c Evaluater.cpp
ThreatPattern.o : ThreatPattern.h ThreatPattern.cpp
	$(CC) $(CFLAGS) -c ThreatPattern.cpp
ThreatUtils.o : ThreatUtils.h ThreatUtils.cpp
	$(CC) $(CFLAGS) -c ThreatUtils.cpp
Gomoku.o : Gomoku.h Gomoku.cpp
	$(CC) $(CFLAGS) -c Gomoku.cpp
NegamaxPlayer.o : NegamaxPlayer.h Cache.h NegamaxPlayer.cpp
	$(CC) $(CFLAGS) -c NegamaxPlayer.cpp
RandomPolicy.o : RandomPolicy.h RandomPolicy.cpp
	$(CC) $(CFLAGS) -c RandomPolicy.cpp
play.o : play.cpp
	$(CC) $(CFLAGS) -c play.cpp


# Phony means not a "real" target, it doesn't build anything
# The phony target "clean" is used to remove all compiled object files.
.PHONY: clean
clean:
	@rm -f $(TARGET) $(OBJECTS)

