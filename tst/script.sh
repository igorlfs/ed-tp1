#!/bin/bash

DIR=int

rm *out.txt
rm *log.txt

for f in *txt; do
    ./binary $f
done

for f in *out.txt; do
    echo "Diff $f"
    diff $f  $DIR/$f
done
