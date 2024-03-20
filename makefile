# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
OBJS = $(SRCS:.c=.o)

# Target executable
TARGET = myshell

# Default target
all: $(BIN_DIR)/$(TARGET)

# Compile object files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Link object files to generate executable
$(BIN_DIR)/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

# Clean up
clean:
	rm -f $(OBJS)
	rm -f $(BIN_DIR)/$(TARGET)
