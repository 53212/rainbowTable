#!/bin/bash

g++ -std=c++17 GenerateRainbowTable/tableGeneration.cpp rainbowTable/sha256.cpp GenerateRainbowTable/main.cpp -o GenerateRainbowTable.o

./GenerateRainbowTable.o

exit 0
