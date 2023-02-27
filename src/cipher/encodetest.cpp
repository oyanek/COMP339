#include <gtest/gtest.h>
#include <iostream>
#include <ostream>
#include <string>

#include "encoder.h"


TEST(encoder_test, is_alphabetic_test_true) {
  ASSERT_TRUE(is_alphabetic("test"));
}

TEST(encoder_test, is_alphabetic_test_true_2) {
  ASSERT_TRUE(is_alphabetic("TesT"));
}

TEST(encoder_test, is_alphabetic_test_false) {
  ASSERT_FALSE(is_alphabetic("1"));
}

TEST(encoder_test, is_alphabetic_test_false_2) {
  ASSERT_FALSE(is_alphabetic("&"));
}

TEST(encoder_test, is_alphabetic_test_false_3) {
  ASSERT_FALSE(is_alphabetic("Te$t"));
}

TEST(encoder_test, encrypt_assert_true){
  ASSERT_EQ(encrypt("AAA", 4), "EEE");
  EXPECT_EQ(encrypt("AAA", 25), "ZZZ");
}

TEST(encoder_test, encrypt_assert_true_2){
  ASSERT_EQ(encrypt("YYY", 4), "CCC");
  EXPECT_EQ(encrypt("ZOO", 5), "ETT");
}

// Test fixtures for dictionary
// struct EncoderDict testing::Test{
//   EncoderDict dictionary = "wordlist.en.txt";

//   EncoderDict(){
//     dict = new dictionary; 
//   }
//   ~EncoderDict(){
//     delete dict;
//   }
// };

// TEST_F(EncoderDict, encrypt_dictionary){
//   EXPECT_STEQ(load_dictionary()), dict);
// }


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}