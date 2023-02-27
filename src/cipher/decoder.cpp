#include <array>
#include <getopt.h>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <map>

#include "decoder.h";

using namespace std;

//map for letter frequency values to perform frequency analysis on
std::map<char, float> freq{{'e', 12.02}, {'t', 9.1},  {'a', 8.12}, {'o', 7.68},
                            {'i', 7.31},  {'n', 6.95}, {'s', 6.28}, {'r', 6.02},
                            {'h', 5.92},  {'d', 4.32}, {'l', 3.98}, {'u', 2.88},
                            {'c', 2.71},  {'m', 2.61}, {'f', 2.30}, {'y', 2.11},
                            {'w', 2.09},  {'g', 2.03}, {'p', 1.82}, {'b', 1.49},
                            {'v', 1.11},  {'k', 0.69}, {'x', 0.17}, {'q', 0.11},
                            {'j', 0.10},  {'z', 0.07}};

//default values for execution
const string DEFAULT_DICTIONARY = "wordlist.en.txt";

//setting default threshold
string arg_dict = DEFAULT_DICTIONARY;
string arg_input;
string arg_output;
float arg_threshold = 100.0;

set<string> words;

inline void parse_arguments(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    string optarg = argv[i];
    if((optarg == "-h" || optarg == "--help")) {
      string help = "Options:\n"\
      "  -h --help    shows this screen\n"\
      "  -d --dict    sets path to dictionary location\n"\
      "  -i --input   sets path to input file\n"\
      "  -o --output  sets path to output file";
      cout << help << endl;
    } else if (optarg == "-d" || optarg == "--dict") {
      arg_dict = argv[++i];
    } else if (optarg == "-i" || optarg == "--input")  {
      arg_input = argv[++i];
    } else if (optarg == "-o" || optarg == "--output") {
      arg_output = argv[++i];
    } else if (optarg == "--threshold") {
      arg_threshold = stof(argv[++i]);
    }
  }
}

//Checks for any characters that are not part of the alphabet
inline bool is_alphabetic(const string & word) {
  for (char c : word) {
    if (!isalpha(c)) {
      return false;
    }
  }
  return true;
}

//load dictionary, error message if dictionary fails to open
inline void loadDictionary() {
  ifstream dict_file(arg_dict);

  if (!dict_file.is_open()) {
    cerr << "Failed to open dictionary file: " << arg_dict << endl;
    exit(1);
  }

// Discards bad words and transforms good words to uppercase before insertion
  string word;
  while (dict_file >> word) {
    if (is_alphabetic(word)) {
      transform(word.begin(), word.end(), word.begin(), ::toupper);
      words.insert(word);
    }
  }
}

//core decryption algorithm performed on each char
char shiftChar(char letter, int shift) {
  int offset = 'A';
  return (char)(((letter - offset - shift + 26) % 26) + offset);
}

//manager function for iterating through a sentence and calling shiftChar 
string decrypt(const string &word, int shift) {
  string sentence;
  for (char ch : word) {
    sentence.push_back(shiftChar(ch, shift));
  }
  return sentence;
}

//beginnning of frequency analysis
int topFreqGuess(string text){
  std::map<char, float> freqCipher;
  std::map<char, float>::iterator it;
  float total = text.length(); 

  //iterate to get most frequent letter count
  for(char ch : text){
    float c = count(text.begin(), text.end(),ch);
    it = freqCipher.find(ch);
    //populate freqCipher with most frequent cipher letter
    if(it == freqCipher.end()) freqCipher[ch]=((c/total) *100); 
  }
  
  char maxChar = 'A';
  float max = 0;

  //get most frequent letter
  for (it = freqCipher.begin(); it != freqCipher.end(); ++it){
    if(it->second > max){
      maxChar = it->first;
      max = it->second;
    }
  }

  //figure out shift for most frequent char to c
  return (((maxChar-'A')-('E'-'A') +26) %26);
}

