#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <ostream>
#include <set>
#include <string>
#include <map>
#include <stdio.h>
#include <stdlib.h>
#include "encoder.hpp"

using namespace std;

//Default values for undeclared command line args
const int DEFAULT_LINE_COUNT = 1;
const int DEFAULT_WORD_LENGTH = 3;
const int DEFAULT_WORDS_PER_SENTENCE = 4;
const string DEFAULT_DICTIONARY = "wordlist.en.txt";
const string DEFAULT_OUTPUT_FILE = "";
const string DEFAULT_INPUT_FILE = "";

//init of non constant variables
int line_count = DEFAULT_LINE_COUNT;
int word_length = DEFAULT_WORD_LENGTH;
int words_per_sentence = DEFAULT_WORDS_PER_SENTENCE;
string dictionary = DEFAULT_DICTIONARY;
string output_file = DEFAULT_OUTPUT_FILE;
string input_file = DEFAULT_INPUT_FILE;
set<string> word_set;

//arguement parser for piped input
void parse_arguments(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    string arg = argv[i];
    if((arg == "-h" || arg == "--help")) {
      string help = "Options:\n"\
      "  -h --help    shows this screen\n"\
      "  -n --lines   sets number of generated lines\n"\
      "  -l --length  sets minimum character length per word\n"\
      "  -w --words   sets words per line\n"\
      "  -d --dict    sets path to dictionary location\n"\
      "  -o --output  sets path to output file";
      cout << help << endl;
      line_count = 0;
    } else if ((arg == "-n" || arg == "--lines") && i + 1 < argc) {
      line_count = atoi(argv[++i]);
    } else if ((arg == "-l" || arg == "--length") && i + 1 < argc) {
      word_length = atoi(argv[++i]);
    } else if ((arg == "-w" || arg == "--words") && i + 1 < argc) {
      words_per_sentence = atoi(argv[++i]);
    } else if ((arg == "-d" || arg == "--dict") && i + 1 < argc) {
      dictionary = argv[++i];
    } else if ((arg == "-o" || arg == "--output") && i + 1 < argc) {
      output_file = argv[++i];
    }
  }
}

//checks for non-alpha symbols
bool is_alphabetic(const string &word) {
  for (char c : word) {
    if (!isalpha(c)) {
      return false;
    }
  }
  return true;
}

//dictionary check
void load_dictionary() {
  ifstream dict_file(dictionary);
  if (!dict_file.is_open()) {
    cerr << "Failed to open dictionary file: " << dictionary << endl;
    exit(1); // return false} return true at end
  }

  string word;
  while (dict_file >> word) {
    //filters words with non-alpha char values
    if (is_alphabetic(word)) {
      transform(word.begin(), word.end(), word.begin(), ::toupper);
      //creates set of strings to be selected from of all viable words
      word_set.insert(word);
    }
  }
}

//creates individual sentence instance in plain text
string generate_sentence() {
  string sentence = "";

  for (int i = 0; i < words_per_sentence; i++) {
    //randomly iterates through word set
    int random_index = rand() % word_set.size();
    auto it = word_set.begin();
    advance(it, random_index);

    string random_word = *it;
    while (random_word.length() < word_length) {
      random_index = rand() % word_set.size();
      it = word_set.begin();
      advance(it, random_index);

      random_word = *it;
    }
    sentence += random_word + " ";
  }

  return sentence;
}

//core encrypt logic 
string encrypt(const string &s, int shift) {
  string result = "";
  for (char c : s) {
    if(c != ' '){
      result += char((c - 'A' + shift) % 26 + 'A');
    }else{
      result += ' ';
    }
  }
  return result;
}
