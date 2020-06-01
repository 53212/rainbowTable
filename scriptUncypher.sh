#!/bin/bash

g++ -std=c++17 Uncypher/uncypher.cpp rainbowTable/sha256.cpp Uncypher/main.cpp -o uncypher.o

./uncypher.o

exit 0
