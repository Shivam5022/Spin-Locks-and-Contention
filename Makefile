# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++20 -Wall

# Source file
SRC = main.cpp locks/tas.cpp locks/ttas.cpp locks/alock.cpp locks/CLHLock.cpp locks/MCSLock.cpp

# Executable name
TARGET = prog
THREADS = 10

# Build rule
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Run rule
run:$(TARGET)
	./$(TARGET) $(THREADS)

# Clean rule
clean:
	rm -f $(TARGET)