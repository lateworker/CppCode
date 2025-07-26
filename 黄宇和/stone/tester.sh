#!/bin/bash
while true; do
    ./gen
    head -n 1 stone.in
    time ./stone
done
