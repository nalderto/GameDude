CXX = g++

# compiler flags:
#  -g     - this flag adds debugging information to the executable file
#  -Wall  - this flag is used to turn on most compiler warnings
CXXFLAGS = -g -Wall

# SDL options
CXX_SDL = -lSDL2

gamedude: main.cpp cpu.cpp cpu.hpp
	$(CXX) $(CXXFLAGS) $(CXX_SDL) $? -o gamedude