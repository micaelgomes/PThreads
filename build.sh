#!/bin/bash
g++ src/main.cpp -pthread -o bin/main && ./bin/main $1 $2