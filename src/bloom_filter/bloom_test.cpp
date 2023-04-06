#include <gtest/gtest.h>
#include <string>
#include "bloom_filter.hpp"

//Change methods to boolean to assert true of false if bloom filter works
//Test the probability of false positive
//Test one hash vs 2 hashes
//Test different bit sizes
//Test search of a word

TEST(bloom_tests, insert_dictionary){
  BloomFilter a(100000, 1);
  ASSERT_TRUE(a.add("Caanaddaian"));
}

TEST(bloom_tests, search_one){
  BloomFilter b(100000, 1);
  b.add("string");
  ASSERT_EQ("Might be in Bloom Filter with false positive probablity 0.0000199999", b.search("string"));
}

TEST(bloom_tests, search_two){
  BloomFilter b(100000, 2);
  b.add("string");
  ASSERT_EQ("Might be in Bloom Filter with false positive probablity 0.0000000036", b.search("string"));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}