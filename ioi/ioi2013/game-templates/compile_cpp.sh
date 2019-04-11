#!/bin/bash

NAME=game

/usr/bin/g++ -DEVAL -static -O2 -std=c++11 -o $NAME grader.c $NAME.cpp
