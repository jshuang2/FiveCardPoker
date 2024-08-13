# Compiler to use
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -std=c11

# Output executable name
TARGET = poker_game

# Source files
SRCS = poker.c deck.c hand.c card.c

# Object files (derived from source files)
OBJS = $(SRCS:.c=.o)

# Default rule: build the program
all: $(TARGET)

# Rule to link the object files into the final executable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

# Rule to compile individual source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule: remove object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets (to avoid conflicts with files of the same name)
.PHONY: all clean
