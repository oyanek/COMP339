#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <set>
#include <string>

using namespace std;

const int DEFAULT_LINE_COUNT = 1;
const int DEFAULT_WORD_LENGTH = 3;
const int DEFAULT_WORDS_PER_SENTENCE = 4;
const string DEFAULT_DICTIONARY = "wordlist.en.txt";
const string DEFAULT_OUTPUT_FILE = "";

int line_count = DEFAULT_LINE_COUNT;
int word_length = DEFAULT_WORD_LENGTH;
int words_per_sentence = DEFAULT_WORDS_PER_SENTENCE;
string dictionary = DEFAULT_DICTIONARY;
string output_file = DEFAULT_OUTPUT_FILE;
set<string> word_set;

void parse_arguments(int argc, char* argv[]) {
  for (int i = 1; i < argc; i++) {
    string arg = argv[i];
    if ((arg == "-n" || arg == "--lines") && i + 1 < argc) {
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

bool is_alphabetic(const string& word) {
  for (char c : word) {
    if (!isalpha(c)) {
      return false;
    }
  }
  return true;
}

void load_dictionary() {
  ifstream dict_file(dictionary);
  if (!dict_file.is_open()) {
    cerr << "Failed to open dictionary file: " << dictionary << endl;
    exit(1);
  }

  string word;
  while (dict_file >> word) {
    if (is_alphabetic(word)) {
      transform(word.begin(), word.end(), word.begin(), ::toupper);
      word_set.insert(word);
    }
  }
}

string generate_sentence() {
  string sentence = "";

  for (int i = 0; i < words_per_sentence; i++) {
    int random_index = rand() % word_set.size();
    auto it = word_set.begin();
    std::advance(it, random_index);

    std::string random_word = *it;
    while (random_word.length() < word_length) {
      random_index = rand() % word_set.size();
      it = word_set.begin();
      std::advance(it, random_index);

      random_word = *it;
    }
    sentence += random_word + " ";
  }

  return sentence;
}

char encryptChar(char c, int shift) {
  if (!isalpha(c)) {
    return c;
  }
  char base = isupper(c) ? 'A' : 'a';
  return char((c - base + shift + 26) % 26 + base);
}

string encrypt(const string& s, int shift) {
  string result = "";
  for (char c : s) {
    result += encryptChar(c, shift);
  }
  return result;
}

int main(int argc, char* argv[]) {
  srand(time(0));
  parse_arguments(argc, argv);
  load_dictionary();

  ofstream output;
  if (!output_file.empty()) {
    output.open(output_file);
    if (!output.is_open()) {
      cerr << "Failed to open output file: " << output_file << endl;
      return 1;
    }
  }
  ostream& out = output_file.empty() ? cout : output;

  for (int i = 0; i < line_count; i++) {
    int shift = rand() % 26;
    string sentence = generate_sentence();
    cout << sentence << endl;
    sentence = encrypt(sentence, shift);
    out << sentence << endl;
  }

  return 0;
}
