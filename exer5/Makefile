# Program name
TARGET = program

# Directories
SRC_DIR = src
BUILD_DIR = .

# Local source files
LOCAL_SRC = $(wildcard *.c)

# Source files in the src folder (if it exists)
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

# Generated object files (placed in the build directory)
OBJ = $(SRC:%.c=$(BUILD_DIR)/%.o)

# Compiler flags
CFLAGS = -Wall -Wextra -g -I. -I$(SRC_DIR)

# Compiler
CC = gcc

# Arguments for the program (can be overridden from the command line)
ARGS ?=

# Default
all: $(TARGET)

# Final compilation (linking object files to create the executable)
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

# Compilation of object files from source files
$(BUILD_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program with arguments
run: $(TARGET)
	./$(TARGET) $(ARGS)

# Run with Valgrind to check for memory leaks
val: $(TARGET)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(TARGET) $(ARGS)

# Clean up build artifacts
clean:
	rm -rf *.o

# Phony targets (targets that are not actual files)
.PHONY: all clean run val