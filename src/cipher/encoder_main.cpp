#include <stdlib.h>
#include "encoder.cpp"

int main(int argc, char *argv[]) {
  srand(time(0));
  parse_arguments(argc, argv);
  load_dictionary(); // if !load dictionary, then exit

  //output file check
  ofstream output;
  if (!output_file.empty()) {
    output.open(output_file);
    if (!output.is_open()) {
      cerr << "Failed to open output file: " << output_file << endl;
      return 1;
    }
  }
  ostream &out = output_file.empty() ? cout : output;
  
  //random caesar shift performed on sentences
  for (int i = 0; i < line_count; i++) {
    int shift = 1 + rand() % 26;
    string sentence = generate_sentence();
    cout << sentence << endl;
    sentence = encrypt(sentence, shift);
    out << sentence << endl;
  }

  return 0;
}