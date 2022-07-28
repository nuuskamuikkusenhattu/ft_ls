#!/bin/bash

./a.out $1 > res_my.txt
ls $1 > res_real.txt

diff "res_my.txt" "res_real.txt" > diff.txt

if [ -s diff.txt ]; then
opendiff diff.txt
fi