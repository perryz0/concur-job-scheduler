// Name: Perry Chien
// Date: 1/28/24
// CSE 374 Homework 3: Wordcount
/*
    TODO: Include basic information.
*/

// TODO: Includes for functions & types defined elsewhere.
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// TODO: Defines for symbolic constants (if any).
#define MAXLINE 500

// TODO: Function declarations/prototypes (with appropriate comments).
// Handles error of no input files passed as argument.
// Parameters:
//   - argc: number of arguments passed
void fileError(int argc);

// Processes a single input file and calculates the number of lines, words, and
// characters based on the specified option (i.e. -l, -w, and -c respectively).
// If no option is specified, the total number of lines are printed.
void fileProcessor();

// TODO: Function definitions.
int main(int argc, char* argv[]) {
    fileError(argc);
    
    // Tracks total number of lines
    int lineTotal = 0;

    // Options tracker (i.e. decides which values out of the three to print)
    int lineBoolean = 0; wordBoolean = 0, charBoolean = 0;

    // Processing all options/flags
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
    printTotal(lineTotal, lineBoolean, wordBoolean, charBoolean);

    return EXIT_SUCCESS;
}

void fileError(int argc) {
    if (argc < 2) {
        printf("Usage: ./wordcount requires an input file.\n");
        return EXIT_FAILURE;
    }
}

void fileProcessor() {

}

// TODO: Remove all TODO comments (like this one) once you are done!
