//
// SYNOPSIS: count_typos dict_filename text_filename [stats_output]
//   cmd-line arguments:
//     dict_filename: the name of the dictionary used to check correct words.
//     text_filename: the name of the file that contains the English plaintext
//                    to run the program on.
//     stats_output: specifies the file to which the program writes the
//                   statistics output. If not provided, those output will be
//                   directed to stdout.
//
// Generates statistics for words, paragraphs and typos in the given file.
//  A word consists on only alphabet characters, and paragraphs are delimited
//  by an instance of "\n\n".
//
// Outputs:
//  - The statistics, to standard output or to a specified file.
//  - There will be a file created in the same directory as the text file, with
//    the same filename except that this output file has a .typos extension
//    after the original filename.
//

// TODO: Import libraries needed to compile

#define TYPOS_SUFFIX ".typos"
#define MAX_WORD_LENGTH 128

// Prints a usage message to stderr
void usage(char* program);

// Formats and prints the given statistics to the given stream.
void show_results(FILE* stream,
                  int word_count, int paragraph_count, int typo_count);

int main(int argc, char* argv[]) {
  Dictionary dict;
  size_t dict_size;
  char buf[MAX_WORD_LENGTH];  // buffer for processing words

  // statistics variables
  int paragraph_count, word_count, typo_count;
  paragraph_count = word_count = typo_count = 0;

  // argument check
  if (argc != 3 && argc != 4) {
    // Print usage and exit
    usage(argv[0]);
  }

  char* input_filename = argv[2];

  // open the input text file
  FILE* text = fopen(input_filename, "r");
  if (!text) {
    fprintf(stderr, "Failed to open %s for input.\n", input_filename);
    return EXIT_FAILURE;
  }

  // open the file for statistics output, or use stdout if not provided
  FILE* stats_output;
  if (argc == 4) {
    char* stats_filename = argv[3];
    stats_output = fopen(stats_filename, "w");
    if (!stats_output) {
      fprintf(stderr, "Failed to open %s for statistics output. Using stdout\n",
                      stats_filename);
      stats_output = stdout;
    }
  } else {
    stats_output = stdout;
  }

  // create the file for typos output, its name should be the input with the
  // ".typos" suffix appended
  FILE* typos_output = NULL;
  char* typos_filename = (char*) malloc(strlen(input_filename));
  strcpy(typos_filename, input_filename);
  strcat(typos_filename, TYPOS_SUFFIX);
  typos_output = fopen(typos_filename, "w");
  if (!typos_output) {
    fprintf(stderr, "Failed to create %s for typos output.\n", typos_filename);
  }

  // build the dictionary
  char* dict_filename = argv[1];
  dict_size = build_dictionary(dict_filename, &dict);
  if (!dict_size) {
    fprintf(stderr, "Failed to build a dictionary from %s.\n", dict_filename);
    return EXIT_FAILURE;
  }

  // process the file
  get_word(buf, MAX_WORD_LENGTH, text);
  while (buf[0] != '\0') {
    if (buf[0] == '\n') {  // a new paragraph
      paragraph_count++;
    } else {  // a new word
      word_count++;
      // spell check
      if (!check_spelling(dict, dict_size, buf)) {
        if (typos_output) {
          fprintf(typos_output, "%s\n", buf);
        }
        typo_count++;
      }
    }
    get_word(buf, MAX_WORD_LENGTH, text);
  }

  // compensate for the offset by 1 of paragraph count
  if (word_count != 0) {
    paragraph_count++;
    show_results(stats_output, word_count, paragraph_count, typo_count);
  } else {
    printf("The text is empty.\n");
  }


  // TODO: Free all allocated resources.

  return EXIT_SUCCESS;
}

void show_results(FILE* stream,
                  int word_count, int paragraph_count, int typo_count) {
  fprintf(stream, "General Statistics\n");
  fprintf(stream, "\t%d words found in the text.\n", word_count);
  fprintf(stream, "\t%d paragraphs found in the text.\n", paragraph_count);
  fprintf(stream, "Typos Statistics\n");
  fprintf(stream, "\t%d mistyped words found in the text.\n", typo_count);
  fprintf(stream, "\tThere is a typo in every %lf words.\n",
          (double) word_count / typo_count);
  fprintf(stream, "\tIn every paragraph, there are %lf typo(s).\n",
          (double) typo_count / paragraph_count);
}

void usage(char* program) {
  printf("Usage: %s dictionary input_text [output]\n", program);
  exit(EXIT_FAILURE);
}
