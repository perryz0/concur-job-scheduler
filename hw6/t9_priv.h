#ifndef T9_PRIV_H_
#define T9_PRIV_H_

// Macros for useful constant values
#define MAX_CHILDREN 8

// Individual T9 TrieNode structure
typedef struct T9 {
    char* nodeWord;
    struct T9* children[MAX_CHILDREN]; // children arr of T9 numbers 2-9
    struct T9* next; // linked list of nodes for the "#" branches
} T9;

#endif  // T9_PRIV_H_
