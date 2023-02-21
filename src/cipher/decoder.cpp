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

//Checks for any characters that are not part of the alphabet
bool isAlphabetic(const string & word) {
  for (char c : word) {
    if (!isalpha(c)) {
      return false;
    }
  }
  return true;
}

//load dictionary, error message if dictionary fails to open
void loadDictionary() {
  ifstream dict_file(arg_dict);

  if (!dict_file.is_open()) {
    cerr << "Failed to open dictionary file: " << arg_dict << endl;
    exit(1);
  }

// Discards bad words and transforms good words to uppercase before insertion
  string word;
  while (dict_file >> word) {
    if (isAlphabetic(word)) {
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

int main(int argc, char *argv[]) {
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

  // Load Dictionary
  loadDictionary();

  //check for output file
  ofstream output;
  if (!arg_output.empty()) {
    output.open(arg_output);
    if (!output.is_open()) {
      cerr << "Failed to open output file: " << arg_output << endl;
      return 1;
    }
  }

  //check for input file
  ifstream input;
  if (!arg_input.empty()) {
    input.open(arg_input);
    if (!output.is_open()) {
      cerr << "Failed to open input file: " << arg_input << endl;
      return 1;
    }
  }

  ostream &out = arg_output.empty() ? cout : output;

  //shift manager
  string line;
  bool firstRun = true;
  while (getline(input.is_open() ? input : cin, line)) {
    int freq_shift = 0;
    int best_shift = -1;
    float best_ratio = 0;
    
    for (int shift = 0; shift < 26; shift++) {
      float ratio = 0;
      int total = 0;

      istringstream line_stream(line);
      string word;
      string mash;

      while (line_stream >> word) {
        mash += word;
        total++;
        string decoded = decrypt(word, shift);
        if (!words.count(decoded))
          continue;
        cout << decoded;
        cout << " ";
        ratio++;
      }

      freq_shift = topFreqGuess(mash);
      
      ratio /= total;
      if (ratio > best_ratio) {
        best_ratio = ratio;
        best_shift = shift;
      }
    }

    // Check if the threshold is reached, return -1 if not met
    if (best_ratio * 100 >= arg_threshold && freq_shift == best_shift) {
      out << best_shift << " same as freq shift"<< endl;
    } else if (best_ratio * 100 >= arg_threshold){
      out << best_shift << endl;
    } else {
      out << -1 << endl;
    }

    cout << endl;
  }

  return 0;
}