#ifndef T9_PRIV_H_
#define T9_PRIV_H_

// Macros for useful constant values
#define MAX_CHILDREN 8
#define MAX_WORD_LENGTH 51

// Individual T9 trie node that stores info about a word and its associated
// T9 number sequence representation.
typedef struct T9 {
    // The current base word stored at the node
    char* currWord;

    // Array that contains child nodes that represent T9 numbers 2-9
    struct T9* children[MAX_CHILDREN];

    // Reference to the next word stored at the current T9 number sequence.
    // The references help to store a list of words associated with the same
    // T9 number sequence.
    struct T9* nextWord;
} T9;

#endif  // T9_PRIV_H_
