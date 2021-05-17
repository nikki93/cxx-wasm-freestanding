#!/bin/bash

PLATFORM="macOS"

if [[ -f /proc/version ]]; then
  if grep -q Linux /proc/version; then
    PLATFORM="lin"
  fi
  if grep -q Microsoft /proc/version; then
    PLATFORM="win"
  fi
fi

case $PLATFORM in
  lin)
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
    ;;
  win)
    clang.exe \
      --target=wasm32 \
      --no-standard-libraries \
      -Wl,--allow-undefined \
      -Wl,--export-all \
      -Wl,--no-entry \
      -std=c++20 \
      -o main.wasm \
      main.cc
    ;;
esac
