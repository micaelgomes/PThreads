#!/bin/bash
g++ main.cpp -pthread -o ../bin/main && time ./../bin/main $1 $2