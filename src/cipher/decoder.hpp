#ifndef _DECODER_H
#define _DECODER_H

#include <string>

extern char shiftChar(char letter, int shift);

extern bool is_alphabetic(const std::string &word);

extern int topFreqGuess(std::string text);

extern char shiftChar(char letter, int shift);

extern std::string decrypt(const std::string &s, int shift);

#endif