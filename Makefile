# Directories
ROOT_DIR    = $(HOME)/Projects/CHIP-8
SRC_DIR     = $(ROOT_DIR)/src
INCLUDE_DIR = $(ROOT_DIR)/include
BUILD_DIR   = $(ROOT_DIR)/build
ROM     	= $(ROOT_DIR)/assets/chip8-test-suite/bin/1-chip8-logo.ch8

# Compiler and flags
CC      = clang
CFLAGS  = -Wall -Wextra -std=c99 -g -I$(INCLUDE_DIR) $(shell pkg-config --cflags sdl3)
LDFLAGS = $(shell pkg-config --libs sdl3)

# Target and sources
TARGET  = chip8
SOURCES = $(SRC_DIR)/chip8.c $(SRC_DIR)/display.c $(SRC_DIR)/input.c $(SRC_DIR)/main.c $(SRC_DIR)/timer.c
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

# Default target
all: $(BUILD_DIR) $(TARGET)

# Ensure build directory exists
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Link the final executable
$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)..."
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Successfully built $(TARGET)"

# Compile .c files into .o files in build/
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

# Run
run: $(TARGET) 
	./$(TARGET) $(ROM) 

# Clean
clean:
	@echo "Cleaning up..."
	rm -rf $(BUILD_DIR) $(TARGET) compile_commands.json
	@echo "Cleanup complete."

.PHONY: all clean run
