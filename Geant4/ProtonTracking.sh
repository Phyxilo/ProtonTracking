#!/bin/bash

count=0
for f in *.fa; do
    #myProgram (options) "./$f" "./$f.tmp" &
    root -l -b -q 'ProtonTracking.C'
    (( count ++ ))        
    if (( count = 2 )); then
        wait
        count=0
    fi
done