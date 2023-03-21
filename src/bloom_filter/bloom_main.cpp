#include <stdlib.h>
#include "bloom_filter.cpp"

///Add CLI

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bloom_filter.hpp"
using namespace std;

// Default values
const long int DEFAULT_NUM_BITS = MAX_BITS;
const int DEFAULT_NUM_HASH = 2;
const string DEFAULT_DICT_FILE = "wordlist.en.txt";

int num_bits = DEFAULT_NUM_BITS;
int num_hash = DEFAULT_NUM_HASH;
string dict_file = DEFAULT_DICT_FILE;

inline void parse_arguments(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    string optarg = argv[i];
    if((optarg == "--help")) {
      string help = "Options:\n"\
      "  -h --help    shows this screen\n"\
      "  -d --dict    sets path to dictionary location\n"\
      "  -b --bits    The number of bits to allocate for the Bloom filter\n"\
      "  -f --hashf   The number of hash functions to try";
      cout << help << endl;
    } else if (optarg == "-d" || optarg == "--dict") {
      dict_file = argv[++i];
    } else if (optarg == "-f" || optarg == "--hashf")  {
      num_hash = atoi(argv[++i]);
    } else if (optarg == "-b" || optarg == "--bits") {
      num_bits = atoi(argv[++i]);
    }
  }
}

int main(int argc, char *argv[]) {
  // Command-line options

  parse_arguments(argc, argv);

  // Read dictionary file
  vector<string> words;
  ifstream ifs(dict_file);
  if (!ifs) {
    cerr << "Failed to open dictionary file: " << dict_file << endl;
    return 1;
  }
  string line;
  while (getline(ifs, line)) {
    words.push_back(line);
  }
  ifs.close();

  // Initialize Bloom filter
   
  BloomFilter bf(num_bits, num_hash);

  // bf.add("one");
  // bf.add("two");
  // bf.add("three");
  
  clock_t start = clock();
  for (const auto &word : words) {
    bf.add(word);
  }
  
  cout << bf.search("test") << endl;
  
  // Add words to Bloom filter
  // clock_t start = clock();
  // for (const auto &word : words) {
  //   bf.add(word);
  // }
  // clock_t end = clock();

  // // Print statistics
  // cout << "Bloom filter statistics:" << endl;
  // cout << "Number of bits: " << num_bits << endl;
  // cout << "Number of hash functions: " << num_hash << endl;
  // cout << "Number of words in dictionary: " << words.size() << endl;
  // cout << "Time to add words to Bloom filter: "
  //      << static_cast<double>((end - start)) / CLOCKS_PER_SEC << " seconds"
  //      << endl;

  // // Test Bloom filter
  // int false_positives = 0;
  // int total_tests = 0;
  // start = clock();
  // vector<string> testWords = {"Hamlet", "Cartoonsishs", "Cartoonsishsguygu"};

  // for (const auto &word : testWords) {
  //     cout << bf.search(word) << endl;
  //     // word is in Bloom filter
  //     if (find(words.begin(), words.end(), word) == words.end()) {
  //       // word is not in dictionary
  //       false_positives++;
  //     }
    
  //   total_tests++;
  // }

  // end = clock();

  // // Print results
  // cout << "Bloom filter testing statistics:" << endl;
  // cout << "Number of tests: " << total_tests << endl;
  // cout << "Number of false positives: " << false_positives << endl;
  // cout << "False positive rate: " << (double)false_positives / total_tests * 100
  //      << "%" << endl;
  // cout << "Time to test Bloom filter: "
  //      << static_cast<double>((end - start)) / CLOCKS_PER_SEC << " seconds"
  //      << endl;

  // return 0;
}
