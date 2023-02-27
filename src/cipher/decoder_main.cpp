#include <stdlib.h>
#include "decoder.cpp"

int main(int argc, char *argv[]) {
  parse_arguments(argc, argv);
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