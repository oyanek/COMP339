#include <algorithm>
#include <cmath>
#include <iterator>
#include <sstream>
#include <stdlib.h>
#include "bloom_filter.hpp"
#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <vector>
#include <iomanip>
#include <openssl/md5.h>
#include <openssl/sha.h>

BloomFilter::BloomFilter(int m, int k) {
  bits = m;
  hashf = k;
  dataV.resize(bits / (sizeof(unsigned long)*8), 0);
  size = dataV.size();
}

std::string dict = "wordlist.en.txt";
int n = 0;

BloomFilter::~BloomFilter() {} 

int hash_fn(string s) {
  hash<string> str_hash;
  return str_hash(s);
}

long long int BloomFilter::h1(string word) {
  unsigned char hash[MD5_DIGEST_LENGTH];
  MD5((unsigned char*)word.c_str(), word.length(), hash);
  string s((char*)hash, MD5_DIGEST_LENGTH);
  // cout << "hash : " << abs(hash_fn(s)) << " data size : " << size << " new hash size : " << hash_fn(s)%size << endl;
  return abs(hash_fn(s)%size);
}

long long int BloomFilter::h2(string word) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256((unsigned char*)word.c_str(), word.length(), hash);
  string s((char*)hash, SHA256_DIGEST_LENGTH);
  return abs(hash_fn(s)%size);
}

void BloomFilter::add(string element){
  if(hashf != 1 && hashf != 2){
    cerr << "No hash function chosen, please enter 1 or 2" <<endl;
  } else if(hashf == 1){
    int hash1 = h1(element) % bits;
    dataV[hash1]++;
    //cout << "first hash : " << hash1 << " value at dataV : " << dataV[hash1] << endl;
  } else if (hashf == 2){
    int hash1 = h1(element) % bits;
    int hash2 = h2(element) % bits;
    dataV[hash1]++;
    dataV[hash2]++;
  }
  n += 1;
}

string BloomFilter::search(string element){
  if(hashf != 1 && hashf != 2){
    cerr << "No hash function chosen, please enter 1 or 2" << endl;
  } else if(hashf == 1){
    int hash1 = h1(element) % bits;
    //cout << "second hash : " << hash1 << " value at dataV : " << dataV[hash1] << endl;
    if(dataV[hash1] == 0){
      return "Not in Bloom Filter";
    }
  } else if (hashf == 2){
    int hash1 = h1(element) % bits;
    int hash2 = h2(element) % bits;
    //cout << "second hash : " << hash1 << " value at dataV : " << dataV[hash1] << " n: " << n << " data size : " << dataV.size() << endl;
    if(dataV[hash1] == 0 || dataV[hash2] == 0){
      return "Not in Bloom Filter";
    }
  }
  double prob = pow(1.0 - pow(1.0 - (1.0/bits), hashf * n), hashf);
  stringstream ss;
  ss << fixed << setprecision(10) << prob;
  return "Might be in Bloom Filter with false positive probablity " + ss.str();
}

// unsigned int hash1(string s) {
//   unsigned int hash = 5381;
//   for (unsigned int i = 0; i < s.size(); i++) {
//     hash = ((hash << 5) + hash) + s[i];
//   }
//   return hash;
// }

// unsigned int hash2(string s) {
//   unsigned int hash = 0;
//   for (int i = 0; i < s.size(); i++) {
//     hash = s[i] + (hash << 6) + (hash << 16) - hash;
//   }
//   return hash;
// }

// BloomFilter::BloomFilter(int m, int k) {
//   num_bits = m;
//   num_hash = k;
//   bits = new bitset<MAX_BITS>(0);
// }

// BloomFilter::~BloomFilter() { delete bits; }

// void BloomFilter::add(string s) {
//   for (int i = 0; i < num_hash; i++) {
//     unsigned int hashval = hash1(s) + i * hash2(s);
//     hashval %= num_bits;
//     bits->set(hashval, true);
//   }
// }

// bool BloomFilter::contains(string s) {
//   for (int i = 0; i < num_hash; i++) {
//     unsigned int hashval = hash1(s) + i * hash2(s);
//     hashval %= num_bits;
//     if (bits->test(hashval) == false) {
//       return false;
//     }
//   }
//   return true;
// }
