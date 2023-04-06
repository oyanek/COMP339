#include "bloom_filter.hpp"
#include <algorithm>
#include <bitset>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <openssl/md5.h>
#include <openssl/sha.h>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
using namespace std;
BloomFilter::BloomFilter(int m, int k) {
  bits = m;
  hashf = k;
  dataV.resize(bits / (sizeof(unsigned long) * 8), 0);
  size = dataV.size();
}

//std::string dict = "wordlist.en.txt";
int n = 0;

int BloomFilter::word_count(){
  return n;
}

int BloomFilter::distinct_word_count(){
  int sum;
  int c = 1;
  for(int x : dataV){
    sum += x;
  }
  if (hashf != 1 && hashf != 2) cerr << "No hash function chosen, please enter 1 or 2" << endl;
  if (hashf == 2) c=2;
  return sum/c;
}

int hash_fn(string s) {
  hash<string> str_hash;
  return str_hash(s);
}

// NTLM possibly third hash

long long int BloomFilter::h1(string word) {
  unsigned char hash[MD5_DIGEST_LENGTH];
  MD5((unsigned char *)word.c_str(), word.length(), hash);
  string s((char *)hash, MD5_DIGEST_LENGTH);
  return abs(hash_fn(s) % size);
}

long long int BloomFilter::h2(string word) {
  unsigned char hash[SHA256_DIGEST_LENGTH];
  SHA256((unsigned char *)word.c_str(), word.length(), hash);
  string s((char *)hash, SHA256_DIGEST_LENGTH);
  return abs(hash_fn(s) % size);
}

bool BloomFilter::add(string element) {
  if (hashf != 1 && hashf != 2) {
    cerr << "No hash function chosen, please enter 1 or 2" << endl;
    return false;
  } else if (hashf == 1) {
    int hash1 = h1(element) % bits;
    dataV[hash1]=1;
  } else if (hashf == 2) {
    int hash1 = h1(element) % bits;
    int hash2 = h2(element) % bits;
    dataV[hash1]=1;
    dataV[hash2]=1;
  }
  n += 1;
  return true;
}

string BloomFilter::search(string element) {
  if (hashf != 1 && hashf != 2) {
    cerr << "No hash function chosen, please enter 1 or 2" << endl;
  } else if (hashf == 1) {
    int hash1 = h1(element) % bits;
    if (dataV[hash1] == 0) {
      return "Not in Bloom Filter";
    }
  } else if (hashf == 2) {
    int hash1 = h1(element) % bits;
    int hash2 = h2(element) % bits;
    if (dataV[hash1] == 0 || dataV[hash2] == 0) {
      return "Not in Bloom Filter";
    }
  }
  double prob = pow(1.0 - pow(1.0 - (1.0 / bits), hashf * n), hashf);
  stringstream ss;
  ss << fixed << setprecision(10) << prob;
  return "Might be in Bloom Filter with false positive probablity " + ss.str();
}

bool BloomFilter::word_count_check(string word){
  string check = search(word);
  if(check == "Not in Bloom Filter"){return true;}else{return false;}
}