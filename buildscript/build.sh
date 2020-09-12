#!/bin/bash
export PATH=$PATH:/usr/local/bin
rm -rf ./build
cmake -B ./build -S ./
make -j4 -C ./build