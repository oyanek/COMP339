#ifndef BLOOM_FILTER_HPP
#define BLOOM_FILTER_HPP

#include <bitset>
#include <string>

///use vector of bool std::vector<bool>

using namespace std;

const int MAX_BITS = 10000000;

unsigned int hash1(string s);
unsigned int hash2(string s);

class BloomFilter {
 public:
  BloomFilter(int, int);
  ~BloomFilter();
  void add(string);
  std::string search(string);
  long long int h1(string word);
  long long int h2(string word);


 private:
  int hashf;
  int bits;
  int size;
  vector<unsigned long> dataV;
};

#endif