# Compiling C++ programs, n.o is made automatically from
# n.cc, n.cpp, or n.C with a recipe of the form
# '$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c'

# CXX is g++ by default
# CPPFLAGS is C Preprocessor flags

CXXFLAGS=-Wall -I../include -I/usr/local/include/SDL
LDFLAGS=-Llibpath -lSDL_ttf -lSDL
SOURCES=../src/main.cpp ../src/disp.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=mem

all: $(SOURCES) $(EXECUTABLE)

# LDFLAGS need to be after the objects, i.e. the order matters for the -l option, see man g++
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@

