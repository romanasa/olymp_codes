#!/bin/bash

problem=wiring

g++ -std=gnu++11 -O2 -pipe -static -o $problem grader.cpp $problem.cpp
