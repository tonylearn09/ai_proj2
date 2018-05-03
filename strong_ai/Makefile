#
#   Makefile for the Hexagonal Gomoku AI
#

#   Change SGBDIR to the directory where all strong_ai files will go:
AIDIR = .

# Target 
TARGET = player13

# Test
TEST_TARGET = play

#   Change SRC_DIR to the directory where strong_ai source files will go:
SRC_DIR = $(AIDIR)/src
TEST_DIR = $(AIDIR)/test

#   Change OBJ_DIR to the directory where strong_ai object files will go:
OBJ_DIR = $(AIDIR)/obj

# List souurce files
SRC = $(wildcard $(SRC_DIR)/*.cpp)
TEST_SRC = $(wildcard $(TEST_DIR)/*.cpp)

# From source files, list object files
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
TEST_OBJ := $(filter-out $(OBJ_DIR)/player13.o,$(OBJ))
TEST_OBJ += $(TEST_SRC:$(TEST_DIR)/%.cpp=$(OBJ_DIR)/%.o)


# Compiler
CC = g++

# Preprocessor flags
CPPFLAGS += -Iinclude

# Complier flags
CFLAGS = -g -O3 -std=c++11

# Linker flags
#LDFLAGS += -Llib

# Third party library
#LDLIBS += -lm

all: $(TARGET) $(TEST_TARGET)

$(TARGET): $(OBJ)
	@$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ && echo "[OK]  $@"

$(TEST_TARGET): $(TEST_OBJ)
	@$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@ && echo "[OK]  $@"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ && echo "[OK]  $@"

$(OBJ_DIR)/$(TEST_TARGET).o: $(TEST_DIR)/$(TEST_TARGET).cpp
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@ && echo "[OK]  $@"

# Phony means not a "real" target, it doesn't build anything
# The phony target "clean" is used to remove all compiled object files.
.PHONY: clean
clean:
	@rm -f $(TARGET) $(OBJ) $(TEST_TARGET) $(TEST_OBJ)

.PHONY: print
print:
	echo $(TEST_OBJ)
