#include <gtest/gtest.h>

#include "decoder.hpp"

TEST(decoder_test, is_alphabetic_test_true) {
  ASSERT_TRUE(is_alphabetic("test"));
}

TEST(decoder_test, is_alphabetic_test_false) {
  ASSERT_FALSE(is_alphabetic("1"));
}

// TEST(decoder_test, decrypt_false){
//   ASSERT_EQ(decrypt("AAA",1), "YYY"); 
// }

TEST(decoder_test, decrypt_true){
  ASSERT_EQ(decrypt("AAA",1), "ZZZ"); 
}









