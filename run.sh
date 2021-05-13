#!/bin/bash

clang++-11 \
  -std=c++20 \
  --target=wasm32 \
  -emit-llvm \
  -c \
  -S \
  main.cc
llc-11 \
  -march=wasm32 \
  -filetype=obj \
  main.ll
wasm-ld-11 \
  --allow-undefined \
  --no-entry \
  --export-all \
  -o main.wasm \
  main.o
