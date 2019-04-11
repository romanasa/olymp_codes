#!/bin/bash
name=findpath

echo "This script compiles solutions in C++"
echo "Compiling $name.cpp..."

g++ --std=c++11 grader.c graderlib.c $name.cpp -o $name $* 
