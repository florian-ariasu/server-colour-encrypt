# Example Makefile for solutions written in C++.

CC = g++
CCFLAGS = -Wall -Wextra -std=c++17 -O0 -lm

.PHONY: build clean

build: p1 p2 p3 p4 p5

# Do not compile here, not even as rule dependencies.
run-p1:
	./p1
run-p2:
	./p2
run-p3:
	./p3
run-p4:
	./p4
run-p5:
	./p5

# Change the source file names (and, if necessary, the executable names - everywhere).
p1: server.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
p2: colouring.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
p3: compression.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
p4: encryption.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
p5: offer.cpp
	$(CC) -o $@ $^ $(CCFLAGS)

# We will delete the executables.
clean:
	rm -f p1 p2 p3 p4 p5
