# Program name
TARGET = program

# Directories
SRC_DIR = src
BUILD_DIR = .

# Local source files
LOCAL_SRC = $(wildcard *.c)

# Source files in the 'src' folder (if it exists)
ifneq ("$(wildcard $(SRC_DIR))","")
    SRC_SRC = $(wildcard $(SRC_DIR)/*.c)
    HEADERS += $(wildcard $(SRC_DIR)/*.h)
else
    SRC_SRC =
endif

# All source files
SRC = $(LOCAL_SRC) $(SRC_SRC)

# Local headers
HEADERS += $(wildcard *.h)

# Generated objects (placed in the build directory)
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)

# Compiler flags
CFLAGS = -Wall -Wextra -g -I. -I$(SRC_DIR)   # Added -g for debug

# Compiler
CC = gcc

# Arguments for the program (can be overridden on the command line)
ARGS ?=

# Default rule
all: $(TARGET)

# Final compilation
$(TARGET): $(OBJ)
    $(CC) $(OBJ) -o $@

# Compilation of objects
$(BUILD_DIR)/%.o: %.c $(HEADERS)
    @mkdir -p $(dir $@)
    $(CC) $(CFLAGS) -c $< -o $@

# Run the program with arguments
run: $(TARGET)
    ./$(TARGET) $(ARGS)

# Run with Valgrind to check for memory leaks (with arguments)
val: $(TARGET)
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TARGET) $(ARGS)

# Clean up
clean:
    rm -rf *.o

.PHONY: all clean run val
