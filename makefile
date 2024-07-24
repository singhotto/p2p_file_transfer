# Makefile

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Wextra -std=c++17

# Include directories
INCLUDES = -Iutils

# Source files
SRCS = main.cpp utils/Server.cc utils/FileManager.cc utils/ThreadPool.cc

# Object files
OBJS = $(SRCS:%.cpp=build/%.o)

# Executable name
TARGET = build/main

# Create the build directory if it doesn't exist
BUILD_DIR = build
$(shell mkdir -p $(BUILD_DIR))

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Rule to build object files
build/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Clean rule to remove generated files
clean:
	rm -f $(BUILD_DIR)/*.o $(TARGET)

.PHONY: all clean
