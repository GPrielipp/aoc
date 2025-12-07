#!/usr/bin/bash

if [ $# -ne 2 ]; then
  echo "usage: $0 <session> <day>"
  exit 1
fi

if [[ "$PWD" =~ "$HOME/aoc/[0-9]{4}" ]]; then
  echo "Please execute this command in the base 'aoc' directory"
  exit 0
fi

SESSION="$1"
DAY=$(($2))
PADDED_DAY=$(printf "%02d" $DAY)

if [ ! -d "day$PADDED_DAY" ]; then
  mkdir "day$PADDED_DAY"
fi

curl -b "session=$SESSION" -o "day$PADDED_DAY/input" "https://adventofcode.com/2025/day/$DAY/input"
cp Makefile "day$PADDED_DAY/"
cp sol.c "day$PADDED_DAY/"
