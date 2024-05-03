#!/bin/bash

for k in $(seq 4 8)
do 
    cd /home/leptjson/leptjson0${k}
    touch leptjson.c leptjson.h test.c CMakeLists.txt
    mkdir build
done