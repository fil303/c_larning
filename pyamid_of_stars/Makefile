# Basic Makefile to build and run a C program

# Compiler and flags
CC = gcc
CFLAGS = -Wall -g

# Source and output
SRC = main.c
OUT = app

# Default target: build and run
all: build run clean

# Build the executable
build:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

# Run the executable
run:
	./$(OUT)

# Clean compiled files
clean:
	rm -f $(OUT)
