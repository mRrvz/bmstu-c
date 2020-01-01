#!/bin/bash

clear
for i in {1..10}; do
    echo "TEST $i"
    ../../app.exe < in_$i.txt > outfile.txt

    if cmp -s "out_$i.txt" "outfile.txt"; then
        echo "Test $i OK"
    else
        echo "Test $i FAILED"
    fi
    echo
done
