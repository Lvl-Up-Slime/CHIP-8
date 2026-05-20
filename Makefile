# Directories
ROOT_DIR    = $(HOME)/Projects/CHIP-8
SRC_DIR     = $(ROOT_DIR)/src
INCLUDE_DIR = $(ROOT_DIR)/include
BUILD_DIR   = $(ROOT_DIR)/build
ROM         = $(ROOT_DIR)/assets/chip8-test-suite/bin/8-scrolling.ch8
SHIFT_QUIRK = --shift-quirk=modern


# Compiler and flags
CC      = clang
CFLAGS  = -Wall -Wextra -std=c99 -g -I$(INCLUDE_DIR) $(shell pkg-config --cflags sdl3)
LDFLAGS = $(shell pkg-config --libs sdl3)

# Target and sources
TARGET  = chip8 
SOURCES = $(SRC_DIR)/chip8.c $(SRC_DIR)/display.c $(SRC_DIR)/input.c $(SRC_DIR)/main.c $(SRC_DIR)/timer.c
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

all: $(BUILD_DIR) $(TARGET)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(OBJECTS)
	@echo "Linking $(TARGET)..."
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Successfully built $(TARGET)"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET) 
	./$(TARGET) $(ROM) 

run_shift: $(TARGET) 
	./$(TARGET) $(SHIFT_QUIRK) $(ROM) 
# Clean
clean:
	@echo "Cleaning up..."
	rm -rf $(BUILD_DIR) $(TARGET) compile_commands.json
	@echo "Cleanup complete."

.PHONY: all clean run
