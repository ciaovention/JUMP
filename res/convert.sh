#!/bin/bash

for f in *.bmp
do
    convert $f XBM:temp.h
    sed "s/static char/const static uint8_t/;s/temp/$f/;s/\.bmp//;s/bits/image/" temp.h > $f.h
done
rm -f temp.h
