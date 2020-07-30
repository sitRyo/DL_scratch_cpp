CXXFLAG=-std=c++17 -Wall
DEBUG=-g -O0

LIBS=../../../lib/
HEADERS=../../../include/

SIGMOID_LIBS=libgnuplot.cpp
SIGMOID_HEADERS=libgnuplot.hpp
SIGMOID_SOURCES=sigmoid.cpp

run: sigmoid.cpp
	g++ $(CXXFLAG) $(LIBS)$(SIGMOID_LIBS) -I$(HEADERS) $(SIGMOID_SOURCES) -o ./bin/sigmoid 
