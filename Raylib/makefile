CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

# Default file if you just type 'make' without specifying
target ?= main

all:
	$(CXX) $(target).cpp -o $(target) $(CXXFLAGS) $(LIBS)