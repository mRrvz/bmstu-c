#!/bin/bash

clear

for i in {1..9}; do
    echo "TEST $i"
    ../../app.exe < pos/in_$i.txt > pos/outfile.txt 2>&1

    if cmp -s "pos/out_$i.txt" "pos/outfile.txt"; then
        echo "Positive Test $i OK"
    else
        echo "Positive Test $i FAILED"
    fi
    echo
done

for i in {1..12}; do
    echo "TEST $i"
    ../../app.exe < neg/in_$i.txt > neg/outfile.txt 2>&1

    if cmp -s "neg/out_$i.txt" "neg/outfile.txt"; then
        echo "Negative Test $i OK"
    else
        echo "Negative Test $i FAILED"
    fi
    echo
done
