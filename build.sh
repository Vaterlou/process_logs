#!/usr/bin/env bash

CPU_CORES=$(getconf _NPROCESSORS_ONLN)
rm -rf build
mkdir -p build && cd build
cmake  ../
make -j $CPU_CORES
