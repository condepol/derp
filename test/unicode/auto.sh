#!/bin/bash
./genuni.py > a.txt
wget http://www.unicode.org/Public/8.0.0/ucd/UnicodeData-8.0.0d8.txt -O ud.txt
./parseUD.py ud.txt > b.txt
cat a.txt b.txt | sort -u > ~/unicode.txt
rm ud.txt a.txt b.txt
