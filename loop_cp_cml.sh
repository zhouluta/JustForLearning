#!/bin/bash

PROJRCT_NAME="leptjson"
FILE="CMakeLists.txt"

for k in $(seq 5 8)
do 
    cp /home/${PROJRCT_NAME}/${PROJRCT_NAME}03/${FILE} /home/${PROJRCT_NAME}/${PROJRCT_NAME}0${k}/${FILE}
done