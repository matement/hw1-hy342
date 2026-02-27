# Variables
CC = gcc
CFLAGS = -Wall -Wextra -pthread -O2
TARGET = src/hw1
SRC = src/main.c

# Default rule
all: $(TARGET)

# Link and Compile
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up build files
clean:
	rm -f $(TARGET)

# Run the program
run: 
	./$(TARGET)