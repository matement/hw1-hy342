# Variables
CC = gcc
CFLAGS = -Wall -Wextra -pthread -O2
TARGET = src/hw1
SRC = src/main.c src/functions.c

# Default rule
all: $(TARGET)

# Link and Compile
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Clean up build files
clean:
	rm -f $(TARGET)

# Run the program
run: $(TARGET)
	./$(TARGET) $(filter-out $@,$(MAKECMDGOALS))

# This dummy rule prevents Make from complaining that '10' is not a target
%:
	@: