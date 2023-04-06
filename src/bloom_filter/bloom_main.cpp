#include <ios>
#include <stdlib.h>
#include "bloom_filter.cpp"
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
//#include <CLI/CLI.hpp>

#include "bloom_filter.hpp"
using namespace std;

// Default values
const long int DEFAULT_NUM_BITS = MAX_BITS;
const int DEFAULT_NUM_HASH = 2;
const string DEFAULT_DICT_FILE = "wordlist.en.txt";
const string DEFAULT_WORD_COUNT = "WOTW.txt";
//const string DEFAULT_WORD_COUNT = "test.txt";

int num_bits = DEFAULT_NUM_BITS;
int num_hash = DEFAULT_NUM_HASH;
string dict_file = DEFAULT_DICT_FILE;
string word_file = DEFAULT_WORD_COUNT;

//CLI App app 

//int main(const int argc, const char *const argv[]) {

  
//}


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

  // Main functionality for word count for War of the Worlds

  vector<string> words;
  ifstream ifs(word_file);
  if (!ifs) {
    cerr << "Failed to open dictionary file: " << word_file << endl;
    return 1;
  }
  string word;
  while (ifs >> word) {
    words.push_back(word);
  }
  ifs.close();

  BloomFilter bf(num_bits, num_hash);

  for (const auto &word : words) {
    bf.add(word);
  }

  bool check = false;
  for (const auto &word : words) {
    check = bf.word_count_check(word);
  }
  
  //bf.word_count_check("notintheWOTW");

  cout << "*********************************" << endl;
  cout << "* WAR OF THE WORLDS WORD COUNTS *" << endl;
  cout << "*********************************" << endl;
  cout << "total number of words: " << bf.word_count() << endl;
  cout << "number of distinct words: " << bf.distinct_word_count() << endl;
  cout << "missed words: " << boolalpha << check << endl;


  // Main functionality for finding test in standard dictionary file
  
  // vector<string> words;
  // ifstream ifs(dict_file);
  // if (!ifs) {
  //   cerr << "Failed to open dictionary file: " << dict_file << endl;
  //   return 1;
  // }
  // string line;
  // while (getline(ifs, line)) {
  //   words.push_back(line);
  // }
  // ifs.close();
   
  // BloomFilter bf(num_bits, num_hash);
  
  // clock_t start = clock();
  // for (const auto &word : words) {
  //   bf.add(word);
  // }
  
  // cout << bf.search("test") << endl;
}
