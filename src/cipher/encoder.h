#ifndef _ENCODER_H
#define _ENCODER_H

#include <string>

extern void parse_arguments(int argc, char *argv[]);

extern bool is_alphabetic(const std::string &word);

extern void load_dictionary();

extern std::string generate_sentence();

extern std::string encrypt(const std::string &s, int shift);

#endif