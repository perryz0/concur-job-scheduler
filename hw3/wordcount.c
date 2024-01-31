// Name: Perry Chien
// Date: 1/28/24
// CSE 374 Homework 3: Wordcount
/*
    TODO: Include basic information.
*/

// TODO: Includes for functions & types defined elsewhere.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// TODO: Defines for symbolic constants (if any).
#define MAXLINE 500

// TODO: Function declarations/prototypes (with appropriate comments).

// Processes a single input file and calculates the number of lines, words, and
// characters based on the specified option (i.e. -l, -w, and -c respectively).
// If no option is specified, the total number of lines are printed.
// Parameters:
//   - filename: Name of current input file to be processed.
//   - lineTotal: Pointer to the tracker for total # of lines across files.
//   - lineBoolean: Boolean that indicates whether to print # of lines.
//   - wordBoolean: Boolean that indicates whether to print # of words.
//   - charBoolean: Boolean that indicates whether to print # of characters.
void fileProcessor(char* filename, int *lineTotal, int lineBoolean,
                                            int wordBoolean, int charBoolean);

// Prints the total number of lines for all files.
// Parameters:
//   - lineTotal: Total # of lines across files.
//   - lineBoolean: Boolean that indicates whether to print # of lines.
//   - wordBoolean: Boolean that indicates whether to print # of words.
//   - charBoolean: Boolean that indicates whether to print # of characters.
void printTotLines(int lineTotal, int lineBoolean, int wordBoolean, int charBoolean);

// TODO: Function definitions.
int main(int argc, char* argv[]) {
    
    // Handles error of no input files passed as argument.
    if (argc < 2 || (argc == 2 && argv[1][0] == '-')) {
        fprintf(stderr, "Usage: ./wordcount requires an input file.\n");
        return EXIT_FAILURE;
    }
    
    // Tracks total number of lines
    int lineTotal = 0;

    // Options tracker (i.e. decides which values out of the three to print)
    int lineBoolean = 0, wordBoolean = 0, charBoolean = 0;

    // Procesis all options/flags
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == 'l') {
                lineBoolean = 1;
            } else if (argv[i][1] == 'w') {
                wordBoolean = 1;
            } else if (argv[i][1] == 'c') {
                charBoolean = 1;
            }
        } else {
            // Process each individual file passed as argument
            fileProcessor(argv[i], &lineTotal, lineBoolean, wordBoolean, charBoolean);
        }
    }

    // Options checker, if no option chosen, total lines will also be printed
    printTotLines(lineTotal, lineBoolean, wordBoolean, charBoolean);

    return EXIT_SUCCESS;
}

/* Non-main helper functions; all descriptions above in the declarations. */

void fileProcessor(char* filename, int *lineTotal, int lineBoolean, int wordBoolean, int charBoolean) {
    FILE *currFile = fopen(filename, "r");
    if (currFile == NULL) {
        printf("%s will not open. Skipping.\n", filename);
        return;
    }

    int lines = 0, words = 0, chars = 0;
    char arr[MAXLINE];

    while (fgets(arr, MAXLINE, currFile) != NULL) {
        lines++;
        
        if (wordBoolean) {
            char *token = strtok(arr, " \n");
            while (token != NULL) {
                words++;
                token = strtok(NULL, " \n");
            }
        } else if (charBoolean) {
            chars += strlen(arr);
        }
    }

    // Closes current file stream
    fclose(currFile);

    // Print the desired values based on options
    if (lineBoolean) {
        printf("%d\n", lines);
    }

    if (wordBoolean) {
        printf("%d\n", words);
    }

    if (charBoolean) {
        printf("%d\n", chars);
    }

    // Update total line value across all files
    *lineTotal += lines;
}

void printTotLines(int lineTotal, int lineBoolean, int wordBoolean, int charBoolean) {
    if (!(lineBoolean || wordBoolean || charBoolean)) {
        printf("Total lines = %d\n", lineTotal);
    }
}

// TODO: Remove all TODO comments (like this one) once you are done!
