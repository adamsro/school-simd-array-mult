all: arraymult

simd.o:		simd.h simd.cpp
		g++  -c  simd.cpp -o simd.o

arraymult:	arraymult.cpp simd.o
		g++  -o arraymult  arraymult.cpp simd.o  -lm  -fopenmp
