#!/bin/bash

make

./pipesort -s 2 -l 3 <small

./pipesort -s 3 -l 6 <small

./pipesort -s 8 -l 10 <small

./pipesort -s 2 -l 10 <small

./pipesort -s 2 -l 3 <large

./pipesort -s 3 -l 6 <large

./pipesort -s 8 -l 10 <large

./pipesort -s 2 -l 10 <large

