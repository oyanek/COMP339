// #include <cstdlib>
// #include <ctype.h>
// #include <iostream>
// #include <map>
// #include <stdio.h>
// #include <fstream>
// #include <vector>
// #include <set>
// #include <string>
// using namespace std;

// //dictionaryInput takes input and reads file

// string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
// int SENTENCES = 25;
// int MIN_SENTENCE_LENGTH = 3;
// int MAX_ADDL_SENTENCE_WORDS = 25;
// string WORDLIST = "aspell -l en dump master";

// //set<string> wordlist = (`aspell -l en dump master`);

// // map for letter frequency values to perform frequency analysis on
// std::map<char, float> freq{{'e', 12.02}, {'t', 9.1},  {'a', 8.12}, {'o', 7.68},
//                            {'i', 7.31},  {'n', 6.95}, {'s', 6.28}, {'r', 6.02},
//                            {'h', 5.92},  {'d', 4.32}, {'l', 3.98}, {'u', 2.88},
//                            {'c', 2.71},  {'m', 2.61}, {'f', 2.30}, {'y', 2.11},
//                            {'w', 2.09},  {'g', 2.03}, {'p', 1.82}, {'b', 1.49},
//                            {'v', 1.11},  {'k', 0.69}, {'x', 0.17}, {'q', 0.11},
//                            {'j', 0.10},  {'z', 0.07}};

// void encrypt(char pText[]) {
//   //creates random num 1-26
//   srand(time(NULL));
//   int rKey = 1 + rand() % 26;
//   char c;
//   // begin iteration over char* pointer
//   for (int i = 0; pText[i] != '\0'; ++i) {
//     //filters for valid chars and retains format of invalid chars
//     if(isalpha(pText[i])){
//       // force uppercase 
//       c = toupper(pText[i]);
//       // all chars in pText are offset by the start of the alphabet a, subtract a first then add key once key is added and offset is removed the mod operation can perform properly and fix overflow.
//       c = (c - 'A' + rKey) % 26 + 'A';
//       // then the offset 'a' can be read creating the new encrypted char value
//       pText[i] = c;
//       // redefine char at i in pText
//     }
//   }
//   std::cout << "Cipher is: " << pText << '\n' << "Key is: " << rKey;
// }

// void decrypt(char pText[], int key) {
//   char c;
//   // begin iteration over char* pointer
//   for (int i = 0; pText[i] != '\0'; ++i) {
//     //filters for valid chars and retains format of invalid chars
//     if(isalpha(pText[i])){
//       //change characters to caps
//       c = toupper(pText[i]);
//       //same logic as encrypt except you add an additional 26 to ensure the mod functions properly
//       int remain = (c - 'A' - key) % 26;
//       if(remain < 0)
//         remain += 26;
//       c = 'A' + remain;
//       pText[i] = c;
//     }
//   }
//   cout << pText;
// }

// int main(int argc, char **argv) {

//   for(int i = 1 ; i < argc ;  )
  
//   ifstream dictionaryInput;
//   //dictionaryInput.open("dictgoeshere.txt");
//   char caesar[300], select;
//   int key;
//   // basic input commands for testing encrypt and decrypt logic
//   // ensure input is caps
//   printf("select mode e/d : ");
//   scanf("%c", &select);
//   if (select == 'e') {
//     printf("Enter Plain Text: ");
//     scanf("%s", &caesar);
//     encrypt(caesar);
//   } 
//   else if (select == 'd'){
//     printf("Enter Cipher: ");
//     scanf("%s", &caesar);
//     printf("Enter Key: ");
//     scanf("%d", &key);
//    decrypt(caesar, key);
//   }
//   return 0;
// }

// /*else if (select == 'D') {
//     printf("Enter Cipher: ");
//     scanf("%s", &caesar);
//     printf("Enter Key: ");
//     scanf("%d", &key);
//     decrypt(caesar, key);
//   } */ 

// /*
// // Should be able to load dictionary, parse lines of input into words,
// void decrypt(char message[], int key) {
//   char ch;
//   for (int i = 0; message[i] != '\0'; ++i) {
//     ch = toupper(message[i]);
    
//     if (ch >= 'a' && ch <= 'z') {
//       ch = ch - key;
//       if (ch < 'a') {
//         ch = ch + 'z' - 'a' + 1;
//       }
//       message[i] = ch;
//     } else if (ch >= 'A' && ch <= 'Z') {
//       ch = ch - key;
//       if (ch > 'a') {
//         ch = ch + 'Z' - 'A' + 1;
//       }
//       message[i] = ch;
//     }
    
//     std::cout << message;
//   }
// }
// */





#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
/*
int main() {
  string command = "aspell -l en dump master";
  FILE *pipe = popen(command.c_str(), "r");

  if (!pipe) {
    cerr << "Could not execute the command." << endl;
    return -1;
  }

  ofstream wordlist("wordlist.txt");
  char buffer[256];
  while (fgets(buffer, 256, pipe) != NULL) {
    wordlist << buffer;
  }

  pclose(pipe);
  wordlist.close();

  return 0;
}
*/


