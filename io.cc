//
// C strings
//

int length(const char *str) {
  int result = 0;
  while (*str != '\0') {
    ++str;
    ++result;
  }
  return result;
}


//
// Console
//

extern "C" void consoleLog(const char *msg, unsigned int msgLen);
void consoleLog(const char *msg) {
  consoleLog(msg, length(msg));
}
