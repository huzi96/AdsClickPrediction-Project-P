#!/bin/bash
for k in $( seq 0 7 )
do
	g++ -D START_LEVEL=${k} main.cpp hash.cpp classes.cpp DataStructure.cpp -o main${k} -O3 -std=c++11
done
