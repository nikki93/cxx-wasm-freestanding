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
      -O3 \
      -std=c++20 \
      -Wno-pragma-once-outside-header \
      --target=wasm32 \
      -emit-llvm \
      -c \
      -S \
      all.cc
    llc-11 \
      -O3 \
      -march=wasm32 \
      -filetype=obj \
      all.ll
    wasm-ld-11 \
      -O3 \
      --allow-undefined \
      --no-entry \
      --export-all \
      -o all.wasm \
      all.o
    ;;
  macOS)
    /opt/homebrew/Cellar/llvm/12.0.1/bin/clang++ \
      -O3 \
      -std=c++20 \
      -Wno-pragma-once-outside-header \
      --target=wasm32 \
      --no-standard-libraries \
      -Wl,--allow-undefined \
      -Wl,--export-all \
      -Wl,--no-entry \
      -o all.wasm \
      all.cc
    ;;
  win)
    clang.exe \
      -O3 \
      -std=c++20 \
      -Wno-pragma-once-outside-header \
      --target=wasm32 \
      --no-standard-libraries \
      -Wl,--allow-undefined \
      -Wl,--export-all \
      -Wl,--no-entry \
      -o all.wasm \
      all.cc
    ;;
esac
