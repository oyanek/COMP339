#include <algorithm>
#include <stdlib.h>
#include "bloom_filter.h"
#include <iostream>
#include <fstream>
#include <bitset>
#include <string>
#include <vector>

#include <openssl/md5.h>

using namespace std;

int hashf = 0;
int bits = 0;
std::string dict = "";

inline void parse_arguments(int argc, char *argv[]) {
  for (int i = 1; i < argc; i++) {
    string optarg = argv[i];
    if((optarg == "--help")) {
      string help = "Options:\n"\
      "  -h --help    shows this screen\n"\
      "  -d --dict    sets path to dictionary location\n"\
      "  -i --input   sets path to input file\n"\
      "  -o --output  sets path to output file";
      cout << help << endl;
    } else if (optarg == "-d" || optarg == "--dict") {
      dict = argv[++i];
    } else if (optarg == "-h" || optarg == "--hashf")  {
      hashf = atoi(argv[++i]);
    } else if (optarg == "-b" || optarg == "--bits") {
      bits = atoi(argv[++i]);
    }
  }
}

/*
inline void loadDictionary() {
  ifstream dict_file(dict);

  if (!dict_file.is_open()) {
    cerr << "Failed to open dictionary file: " << dict << endl;
    exit(1);
  }
// Discards bad words and transforms good words to uppercase before insertion
  string word;
  while (dict_file >> word) {
    if (is_alphabetic(word)) {
      transform(word.begin(), word.end(), word.begin(), ::toupper);
      words.insert(word);
    }
  } }
*/

void add(){}
/*
    def insert(self, element):
        if self.k == 1:
            hash1 = h1(element) % self.m
            self.data[hash1] = 1
        elif self.k == 2:
            hash1 = h1(element) % self.m
            hash2 = h2(element) % self.m
            self.data[hash1] = 1
            self.data[hash2] = 1
        self.n += 1
  */

/*
def insert(string element){

}
*/

string search(){
  return "in dev";
}
/*
def search(self, element):
        if self.k == 1:
            hash1 = h1(element) % self.m
            if self.data[hash1] == 0:
                return "Not in Bloom Filter"
        elif self.k == 2:
            hash1 = h1(element) % self.m
            hash2 = h2(element) % self.m
            if self.data[hash1] == 0 or self.data[hash2] == 0:
                return "Not in Bloom Filter"
        prob = (1.0 - ((1.0 - 1.0/self.m)**(self.k*self.n))) ** self.k
        return "Might be in Bloom Filter with false positive probability "+str(prob)

*/

/*
def h1(w):
    h = hashlib.md5(w)
    return hash(h.digest().encode('base64')[:6])%10

def h2(w):
    h = hashlib.sha256(w)
    return hash(h.digest().encode('base64')[:6])%10
*/

