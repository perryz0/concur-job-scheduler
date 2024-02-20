// Name: Perry Chien
// Date: 2/19/24
// CSE 374 Homework 6: T9 Implementation
/*
    This is a program that simulates the functionalities of a T9 predictive
    text system. It provides functions for initializing an empty T9 dictionary,
    loading words from a file into the dictionary, adding words to dictionary,
    predicting words based on T9 number sequences, and destroying a dictionary
    to free memory. The implementation utilizes a trie data structure to store
    and retrieve words based on their T9 representations. It also checks input
    validity to ensure only valid T9 key sequences are processed.
*/

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t9_lib.h"
#include "t9_priv.h"


// HELPER FUNCTION/PROTOTYPE DECLARATIONS (with comments)

// Helps translate letters to corresponding keypad digits. Returns a digit
// between 2 and 9 inclusive if the letter is a valid lowercase English
// letter. Otherwise, a value of -1 is returned, indicating invalid input.
// Parameters:
//   - letter: Letter (part of a word) being translated into T9 number digit
int charToDigit(char letter);

// Helps initialize an empty children array of number nodes.
// Parameters:
//   - parent: Pointer to the T9 node whose child number nodes are initialized
void initializeChildNodes(T9* parent);


// FUNCTION IMPLEMENTATIONS (comments & pre-/post- conditions in header file)

T9* InitializeEmptyT9() {
    T9* dict = (T9*)malloc(sizeof(T9));

    // Initialize root node so it holds no word and no garbage values
    dict->currWord = NULL;

    // Initialize empty children for new root node
    initializeChildNodes(dict);

    // To initialize an empty linked list
    dict->nextWord = NULL;
    return dict;
}

T9* InitializeFromFileT9(const char* filename) {

    // Create empty T9 dictionary to start initialization
    T9* dict = InitializeEmptyT9();

    // Open new file stream to initialize file
    FILE* file = fopen(filename, "r");

    // Handles non-existent file error
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        fclose(file);
        return NULL;
    }

    // Max word length 50 and +1 for null terminator
    char word[51]; 

    // Iterate through each line (i.e. 1 line = 1 word) in the file
    while (fgets(word, sizeof(word), file) != NULL) {
        // Remove newline character for each line of word in file
        size_t length = strlen(word);
        if (word[length - 1] == '\n') {
            word[length - 1] = '\0';
        }
        AddWordToT9(dict, word);
    }

    // Dealloc file stream after use
    fclose(file);
    return dict;
}

void AddWordToT9(T9* dict, const char* word) {
    
    // Start traversal from the root
    T9* current = dict;

    // Trie traversal until null terminator is hit
    for (int i = 0; word[i] != '\0'; ++i) {

        // Initialize current keypad digit
        int digit = charToDigit(word[i]);

        // Checks if the number digit exists within the child or not
        if (current->children[digit] == NULL) {

            // Allocates memory for the new number digit
            current->children[digit] = (T9*)malloc(sizeof(T9));

            // Initialize keypad digit children to be empty
            initializeChildNodes(current->children[digit]);

            // Assign no word/linked list stored at the new number digit
            current->children[digit]->currWord = NULL;
            current->children[digit]->nextWord = NULL;
        }

        // Traverses current to the child node that matches the digit
        current = current->children[digit];
    }

    // Post-traversal: Checks if word already exists in dictionary
    if (current->currWord == NULL) {

        // Allocate memory and add the new word to T9 dictionary
        current->currWord = (char*)malloc((strlen(word) + 1) * sizeof(char));
        strncpy(current->currWord, word, strlen(word) + 1);
    } else {
        // The T9 number sequence already exists, add word into linked list
        while (current->nextWord != NULL) {
            // Traverse down the linked list
            current = current->nextWord;
        }

        // Initialize, allocate memory, and add new word to end of linked list
        current->nextWord = (T9*)malloc(sizeof(struct T9*));
        current->nextWord->currWord = (char*)malloc((strlen(word) + 1) * sizeof(char));
        strncpy(current->nextWord->currWord, word, strlen(word) + 1);

        // Assign null linked list and child number nodes to the new word
        initializeChildNodes(current->nextWord);
        current->nextWord->nextWord = NULL;
    }
}

char* PredictT9(T9* dict, const char* nums) {
    if (nums == NULL) {
        return NULL;
    }

    // Starts traversal from the root
    T9* current = dict;
    int numPounds = 0;

    // Iterates through each digit of the number sequence pointed by nums
    for (size_t i = 0; nums[i] != '\0'; i++) {
        if (nums[i] == '#') {
            numPounds++;

            // Handles invalid input where '#' is at the beginning
            if (i == 0) {
                return NULL;
            }
        } else {
            // Handles invalid input where digits come after first '#'
            if (numPounds != 0) {
                return NULL;
            }

            // Extracts current digit value
            int digit = nums[i] - '0';

            // Checks if the digit is a valid number between 2 and 9 inclusive
            if (digit < 2 || digit > 9) {
                return NULL;
            }

            // Checks existing num sequences thus far in T9 dictionary
            if (current->children[digit] == NULL) {
                return NULL;
            }

            // Move down the trie to next number digit
            current = current->children[digit];
        }
    }

    // Traverse through the linked list if input has pound signs
    while (numPounds > 0 && current != NULL && current->nextWord != NULL) {
        current = current->nextWord;
        numPounds--;
    }

    // Return the word if found, otherwise return NULL
    return (numPounds == 0) ? current->currWord : NULL;
}

void DestroyT9(T9* dict) {
    // Recursively traverse through the Trie and destroy child nodes
    for (int i = 0; i < MAX_CHILDREN; i++) {
        if (dict->children[i] != NULL) {
            DestroyT9(dict->children[i]);
        }
    }

    // Destroy linked list of "#" key stored nodes
    T9* current = dict->nextWord;
    while (current != NULL) {
        T9* temp = current;
        current = current->nextWord;
        free(temp->currWord);
        free(temp);
    }

    // Free memory for the current node
    free(dict->currWord);
    free(dict);
}


// HELPER FUNCTION DEFINITIONS (comments above in declarations)

int charToDigit(char letter) {
    if (letter >= 'a' && letter <= 'c') return 2;
    if (letter >= 'd' && letter <= 'f') return 3;
    if (letter >= 'g' && letter <= 'i') return 4;
    if (letter >= 'j' && letter <= 'l') return 5;
    if (letter >= 'm' && letter <= 'o') return 6;
    if (letter >= 'p' && letter <= 's') return 7;
    if (letter >= 't' && letter <= 'v') return 8;
    if (letter >= 'w' && letter <= 'z') return 9;
    return -1;
}

void initializeChildNodes(T9* parent) {
    for (int i = 0; i < MAX_CHILDREN; ++i) {
        parent->children[i] = NULL;
    }
}