#include "meta.cc"
#include "io.cc"


struct Test1 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test2 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test3 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test4 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test5 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test6 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test7 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test8 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test9 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test10 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test11 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test12 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test13 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test14 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test15 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test16 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test17 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test18 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test19 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test20 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test21 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test22 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test23 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test24 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test25 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test26 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test27 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test28 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test29 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test30 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test31 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test32 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test33 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test34 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test35 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test36 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test37 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct Test38 {
  PROP(int, foo) = 42;
  PROP(const char *, bar) = "hello, world!";
};

struct TestAll {
  PROP(Test1, test1);
  PROP(Test2, test2);
  PROP(Test3, test3);
  PROP(Test4, test4);
  PROP(Test5, test5);
  PROP(Test6, test6);
  PROP(Test7, test7);
  PROP(Test8, test8);
  PROP(Test9, test9);
  PROP(Test10, test10);
  PROP(Test11, test11);
  PROP(Test12, test12);
  PROP(Test13, test13);
  PROP(Test14, test14);
  PROP(Test15, test15);
  PROP(Test16, test16);
  PROP(Test17, test17);
  PROP(Test18, test18);
  PROP(Test19, test19);
  PROP(Test20, test20);
  PROP(Test21, test21);
  PROP(Test22, test22);

  struct More {
    PROP(Test23, test23);
    PROP(Test24, test24);
    PROP(Test25, test25);
    PROP(Test26, test26);
    PROP(Test27, test27);
    PROP(Test28, test28);
    PROP(Test29, test29);
    PROP(Test30, test30);
    PROP(Test31, test31);
    PROP(Test32, test32);
    PROP(Test33, test33);
    PROP(Test34, test34);
    PROP(Test35, test35);
    PROP(Test36, test36);
    PROP(Test37, test37);
    PROP(Test38, test38);
  };
  PROP(More, more);
};

void consoleLogFieldNames(auto &value) {
  forEachProp(value, [&]<typename P>(P &prop) {
    if constexpr (isAggregate<typename P::Value>) {
      consoleLogFieldNames(prop());
    } else {
      consoleLog(P::name);
    }
  });
}

extern "C" void init() {
  TestAll testAll;
  consoleLogFieldNames(testAll);
}
