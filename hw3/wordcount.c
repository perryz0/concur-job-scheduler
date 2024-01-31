// Name: Perry Chien
// Date: 1/28/24
// CSE 374 Homework 3: Wordcount
/*
    TODO: Include basic information.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Max compatible line length of input file
#define MAXLINE 500



// FUNCTION DECLARATIONS (with comments)

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
void totalLines(int lineTotal, int lineBoolean, int wordBoolean,
                                                        int charBoolean);



// FUNCION DEFINITIONS

int main(int argc, char* argv[]) {
    
    // Handles error of no input files passed as argument.
    if (argc < 2 || (argc == 2 && argv[1][0] == '-' && strlen(argv[1]) == 2
         && (argv[1][1] == 'l' || argv[1][1] == 'w' || argv[1][1] == 'c'))) {

        fprintf(stderr, "Usage: ./wordcount requires an input file.\n");
        return EXIT_FAILURE;
    }
    
    // Tracks total number of lines
    int lineTotal = 0;

    // Options tracker (i.e. decides which values out of the three to print)
    int lineBoolean = 1, wordBoolean = 1, charBoolean = 1;

    // Process all options/flags
    for (int i = 1; i < argc; i++) {
        if (i == 1 && strncmp((argv[i]), "-l", 3) == 0) {
            wordBoolean = 0, charBoolean = 0;
        } else if (i == 1 && strncmp((argv[i]), "-w", 3) == 0) {
            lineBoolean = 0, charBoolean = 0;
        } else if (i == 1 && strncmp((argv[i]), "-c", 3) == 0) {
            lineBoolean = 0, wordBoolean = 0;
        } else {

            // Process each individual file passed as argument
            fileProcessor(argv[i], &lineTotal, lineBoolean, wordBoolean,
                                                                charBoolean);
        }
    }

    // Checker and printer for total lines
    totalLines(lineTotal, lineBoolean, wordBoolean, charBoolean);

    return EXIT_SUCCESS;
}



/* Non-main helper functions; all descriptions above in the declarations. */

void fileProcessor(char* filename, int *lineTotal, int lineBoolean,
                                            int wordBoolean, int charBoolean) {

    FILE *currFile = fopen(filename, "r");
    int lines = 0, words = 0, chars = 0;

    if (currFile == NULL) {
        fprintf(stderr, "%s will not open. Skipping.\n", filename);
        return;
    }

    char arr[MAXLINE];

    while (fgets(arr, MAXLINE, currFile) != NULL) {
        lines++;
        
        if (charBoolean) {
            chars += strlen(arr);
        }

        if (wordBoolean) {
            char *token = strtok(arr, " \n");
            while (token != NULL) {
                words++;
                token = strtok(NULL, " \n");
            }
        }
    }

    // Closes current file stream
    fclose(currFile);

    // Print the desired values based on options
    if (lineBoolean && wordBoolean && charBoolean) {
        printf("%d %d %d %s\n", lines, words, chars, filename);
    } else {
        if (lineBoolean) {
            printf("%d\n", lines);
        }

        if (wordBoolean) {
            printf("%d\n", words);
        }

        if (charBoolean) {
            printf("%d\n", chars);
        }
    }

    // Update total line value across all files
    *lineTotal += lines;
}

void totalLines(int lineTotal, int lineBoolean, int wordBoolean,
                                                    int charBoolean) {
    if (lineBoolean && wordBoolean && charBoolean) {
        printf("Total Lines = %d\n", lineTotal);
    }
}
