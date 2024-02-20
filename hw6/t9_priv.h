#ifndef T9_PRIV_H_
#define T9_PRIV_H_

// Macros for useful constant values
#define MAX_CHILDREN 8

// Individual TrieNode structure
typedef struct TrieNode {
    char* word;
    struct TrieNode* children[MAX_CHILDREN]; // arr of prefixes that branch out
    struct TrieNode* next; // linked list of nodes for the "#" branches
};

typedef struct T9 {
    // TODO: what fields should this struct have?
    // You can use this struct as a node in your trie
    
    TrieNode* root;
} T9;

#endif  // T9_PRIV_H_
