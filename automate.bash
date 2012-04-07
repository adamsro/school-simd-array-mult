#!/bin/csh

foreach n { 1000 2000 4000 8000 16000 32000 64000 128000 256000 512000 1024000 2048000 4096000 8192000 } 
echo " "
echo NUM = $n
g++  -DNUM=$n  -o arraymult  arraymult.cpp simd.o  -lm  -fopenmp
./arraymult
end
