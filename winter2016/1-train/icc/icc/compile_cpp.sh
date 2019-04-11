#!/bin/bash

NAME=icc
g++ -std=c++11 -O2 -static grader.cpp $NAME.cpp -o $NAME 2>&1
