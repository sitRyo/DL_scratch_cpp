CXXFLAG=-std=c++17 -Wall
DEBUG=-g -O0

LIBS=../../../lib/
HEADERS=../../../include/

RELU_LIBS=libgnuplot.cpp
RELU_HEADERS=libgnuplot.hpp
RELU_SOURCES=ReLU.cpp

run: ReLU.cpp
	g++ $(CXXFLAG) $(LIBS)$(RELU_LIBS) -I$(HEADERS) ReLU.cpp -o ./bin/ReLU 
