#include <iostream>
#include <gtest/gtest.h>

int main(int charv, char **argv){
  testing InitGoogleTest::(&argc, argv);
  return RUN_ALL_TESTS();
}
