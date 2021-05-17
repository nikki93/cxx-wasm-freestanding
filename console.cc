#pragma once
#include "all.cc"


extern "C" void consoleLog(const char *msg, unsigned int msgLen);
void consoleLog(const char *msg) {
  consoleLog(msg, length(msg));
}
