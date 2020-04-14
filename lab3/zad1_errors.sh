#!/bin/bash
for i in {1..50}
do
    ./zad1.sh $i >> zad1_errors.txt
done