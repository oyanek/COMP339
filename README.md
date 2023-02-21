Our project consists of an encode and decode feature that that takes input derived from the aspell dictionary. From the command line, you can set number of lines, minimum word length, dictionary, output file, and words per line. The encoder removes all non-alphabetic characters and converts lowercase to uppercase. Sentences are randomly created and shifted. Output is sent to a txt file. Decoder takes input from the encoder's output and performs a decrypt to finds keys to decrypt each sentence. Keys are provided in an output file as well as a frequency analysis. The larger the intial data set, the more accurate the frequency analysis is. Tests are currently in the works and will be available by next class meeting. 

## SOURCES USED:
### For Encrypt and Decrypt Mod Equation: 
- https://en.wikipedia.org/wiki/Caesar_cipher
### Example of Program in C:
- https://www.scaler.com/topics/caesar-cipher-program-in-c/
### Freq. Analysis in Python:
- https://medium.com/@momohakarish/caesar-cipher-and-frequency-analysis-with-python-635b04e0186f#:~:text=Frequency%20Analysis%20And%20Breaking%20The,to%20break%20the%20Caeser%20Cipher.
### Rand. Number:
- https://stackoverflow.com/questions/28656004/c-random-doesnt-workreturns-same-value-always
### For file opening and reading:
- https://stackoverflow.com/questions/29441631/cannot-open-file-with-relative-path-c-ifstream
### Entry demo for gtests:
- https://www.youtube.com/watch?v=16FI1-d2P4E
### Others
C++ tutorial provided in teams along with dozens of other C++ videos for basic knowledge of the language