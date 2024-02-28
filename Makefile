# Makefile for compiling main.cpp, server.cc, and ClientSession.cc with Muduo library

# Compiler and compiler flags
CXX = g++
CXXFLAGS =-std=c++11 

# Source files and output executable
SRC = test.cpp QueryResult.cpp Field.cpp MySQLTool.cpp
EXE = test

# Muduo library path
#MUDUO_PATH = /path/to/muduo

# Include and library paths
INC_PATH = -I/usr/local/mysql/include
LIB_PATH = -L/usr/local/mysql/lib -lmysqlclient

# Default target
all: $(EXE)

# Rule to build the executable
$(EXE): $(SRC)
	$(CXX) -o $@ $^ $(INC_PATH) $(LIB_PATH) $(CXXFLAGS) 

# Clean up intermediate files and the executable
clean:
	rm -f $(EXE)

.PHONY: all clean