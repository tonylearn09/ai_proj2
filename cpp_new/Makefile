# Configuration:
CC = g++
CFLAGS = -g -O3 -std=c++11

SOURCES = Move.cpp State.cpp Field.cpp Evaluater.cpp ThreatPattern.cpp \
		  ThreatUtils.cpp Gomoku.cpp NegamaxPlayer.cpp RandomPolicy.cpp play.cpp player13.cpp
OBJECTS = Move.o State.o Field.o Evaluater.o ThreatPattern.o \
		  ThreatUtils.o Gomoku.o NegamaxPlayer.o RandomPolicy.o play.o
PLAYER_OBJECTS = Move.o State.o Field.o Evaluater.o ThreatPattern.o \
		  ThreatUtils.o Gomoku.o NegamaxPlayer.o RandomPolicy.o player13.o
TARGET = play
PLAYER_TARGET = player13

# Buid rule
all : $(TARGET) $(PLAYER_TARGET)
$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^
$(PLAYER_TARGET) : $(PLAYER_OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

Move.o : Move.h Move.cpp
	$(CC) $(CFLAGS) -c Move.cpp
Field.o : Field.h Field.cpp
	$(CC) $(CFLAGS) -c Field.cpp
State.o : State.h Move.h Field.h State.cpp
	$(CC) $(CFLAGS) -c State.cpp
Evaluater.o : Evaluater.h Field.h State.h Evaluater.cpp
	$(CC) $(CFLAGS) -c Evaluater.cpp
ThreatPattern.o : ThreatPattern.h ThreatPattern.cpp
	$(CC) $(CFLAGS) -c ThreatPattern.cpp
ThreatUtils.o : ThreatUtils.h ThreatPattern.h Move.h State.h Field.h ThreatUtils.cpp
	$(CC) $(CFLAGS) -c ThreatUtils.cpp
Gomoku.o : Gomoku.h Move.h Gomoku.cpp
	$(CC) $(CFLAGS) -c Gomoku.cpp
NegamaxPlayer.o : NegamaxPlayer.h Cache.h Move.h State.h Evaluater.h Gomoku.h ThreatUtils.h NegamaxPlayer.cpp
	$(CC) $(CFLAGS) -c NegamaxPlayer.cpp
RandomPolicy.o : RandomPolicy.h RandomPolicy.cpp
	$(CC) $(CFLAGS) -c RandomPolicy.cpp
play.o : Gomoku.h RandomPolicy.h NegamaxPlayer.h Move.h play.cpp
	$(CC) $(CFLAGS) -c play.cpp
player13.o : Gomoku.h NegamaxPlayer.h Move.h player13.cpp
	$(CC) $(CFLAGS) -c player13.cpp


# Phony means not a "real" target, it doesn't build anything
# The phony target "clean" is used to remove all compiled object files.
.PHONY: clean
clean:
	@rm -f $(TARGET) $(OBJECTS) $(PLAYER_TARGET) $(PLAYER_OBJECTS)

