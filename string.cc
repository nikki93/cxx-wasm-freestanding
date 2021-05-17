#pragma once
#include "all.cc"


//
// Null-terminated strings
//

int length(const char *str) {
  int result = 0;
  while (*str != '\0') {
    ++str;
    ++result;
  }
  return result;
}
