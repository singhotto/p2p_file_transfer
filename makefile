# Makefile

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Include directories
INCLUDES = -Iutils

# Source files
SRCS = main.cpp utils/Server.cc

# Object files
OBJS = main.o utils/Server.o

# Executable name
TARGET = main

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Rule to build main.o
main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c main.cpp -o main.o

# Rule to build utils/Server.o
utils/Server.o: utils/Server.cc
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c utils/Server.cc -o utils/Server.o

# Clean rule to remove generated files
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
