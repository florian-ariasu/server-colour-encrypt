CC = g++
CCFLAGS = -Wall -Wextra -std=c++17 -O0 -lm

.PHONY: build clean

build: p1 p2 p3 p4 p5

# Run commands
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

# Compilation rules (updated to use src/)
p1: src/server.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
p2: src/colouring.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
p3: src/compression.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
p4: src/encryption.cpp
	$(CC) -o $@ $^ $(CCFLAGS)
p5: src/offer.cpp
	$(CC) -o $@ $^ $(CCFLAGS)

# Cleanup
clean:
	rm -f p1 p2 p3 p4 p5
	rm -f *.out
