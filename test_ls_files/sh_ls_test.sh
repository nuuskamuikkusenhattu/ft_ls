#!/bin/bash

./a.out $1 > res_my.txt
ls $1 > res_real.txt

if [ -s diff.txt ]; then
opendiff "res_my.txt" "res_real.txt"
fi