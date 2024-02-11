// Module for binary-search-lookup dictionary
// Declarations of functions in the spellchecker module
//
// To use this dictionary module: you dictionary must satisfy the following
// requirements:
//    - has one and only one word on each line
//    - the words are sorted in ASCII order
//    - the file needs to be terminated with a \n, before EOF.
//
// YOU MAY NOT CHANGE THE CONTENT OF THIS FILE.

#ifndef _SPELLCHECKER
#define _SPELLCHECKER

typedef char** Dictionary;

// filename is the name of the file to build a dictionary from
// returns the number of words in the built dictionary, or 0 if the
// operation fails
// params:
//      filename:     the name of the file to build a dictionary from, the file
//                    needs to be sorted in ASCII order for it to have the
//                    correct behavior
//      dict_result:  output parameter, a pointer to a Dictionary. After a
//                    successful execution, the Dictionary will be set to the
//                    completed dictionary; transfers ownership of the
//                    dictionary to the caller.
// returns: the size of the dictionary, or 0 on failure/empty file
size_t build_dictionary(char *filename, Dictionary* dict_result);

// frees the given dictionary
// params:
//      dict:   the dictionary to be freed
//      size:   the size of the dictionary
void free_dictionary(Dictionary dict, size_t size);

// returns 1 if the word exists in the dictionary,
//         0 otherwise
// params:
//      dict:   the dictionary to look up from
//      size:   the size of the dictionary
//      word:   the word to check
int check_spelling(Dictionary dict, size_t size, char* word);

#endif  // _SPELLCHECKER
