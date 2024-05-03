#!/bin/bash

PROJECT_NAME="leptjson"
PROJECT_DIR="/home/${PROJECT_NAME}"

for k in $(seq 1 8)
do
    cd ${PROJECT_DIR}/${PROJECT_NAME}0${k}/build
    make clean
done
