#!/bin/bash

WORK_PATH=tests/func_tests

clear

for i in {1..9}; do
    echo "TEST $i"
    ./app.exe < $WORK_PATH/pos/in_0$i.txt > $WORK_PATH/pos/outfile.txt 2>&1

    if cmp -s "$WORK_PATH/pos/out_0$i.txt" "$WORK_PATH/pos/outfile.txt"; then
        echo "Positive Test $i OK"
    else
        echo -e "Real: "
        cat $WORK_PATH/pos/outfile.txt
        echo -e "\nExpected: "
        cat $WORK_PATH/pos/out_0$i.txt
        echo -e "\nPositive Test $i FAILED"
    fi
    echo
done
