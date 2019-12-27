#!/bin/bash

clear

for i in {1..9}; do
    echo "TEST $i"
    ../../app.exe < Positive/in_$i.txt > Positive/outfile.txt 2>&1

    if cmp -s "Positive/out_$i.txt" "stockpile.txt"; then
        echo "Positive Test $i OK"
    else
        echo "Positive Test $i FAILED"
    fi
    echo
done

for i in {1..6}; do
    echo "TEST $i"
    ../../app.exe < Negative/in_$i.txt > Negative/outfile.txt 2>&1

    if cmp -s "Negative/out_$i.txt" "Negative/outfile.txt"; then
        echo "Negative Test $i OK"
    else
        echo "Negative Test $i FAILED"
    fi
    echo
done
