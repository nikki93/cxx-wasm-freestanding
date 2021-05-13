extern "C" void consoleLog(const char *msg, unsigned int msgLen);

extern "C" void init() {
  const char msg[] = "hello, world!";
  consoleLog(msg, sizeof(msg) - 1);
}
