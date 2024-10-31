# Makefile to compile main.cc using clang++

# Compiler
CXX = clang++

# Compiler flags
CXXFLAGS = -std=c++17

# SDL2 flags
SDL2_FLAGS = $(shell pkg-config --cflags --libs sdl2)

# Target executable
TARGET = main.exe

# Source files
SRC = src/main.cc

# Build target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(SDL2_FLAGS)

# Clean target
clean:
	rm -f $(TARGET)