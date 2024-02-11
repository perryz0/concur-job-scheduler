// TODO: Import libraries needed to compile.

#define MAX_WORD_SIZE 128
#define DEFAULT_DICT_SIZE (1 << 16)  // same as 2^16, an arbitrary starting size

size_t build_dictionary(char* filename, Dictionary* dict_result) {
  // allocate space for the dictionary
  size_t dict_size = DEFAULT_DICT_SIZE;
  Dictionary dict = (Dictionary) malloc(dict_size);

  // create a buffer to store the lines
  char* buffer = (char*) malloc(MAX_WORD_SIZE);
  size_t buffer_len = MAX_WORD_SIZE;

  // open the file for reading
  FILE* input = fopen(filename, "r");
  if (!input) {
    return 0;
  }

  size_t word_count = 0;
  char* line = fgets(buffer, buffer_len, input);
  size_t word_len = strlen(buffer);
  // needs to check for \n at the end because fgets reads in \n as well
  if (buffer[word_len - 1] == '\n') {
    // Remove the newline from the word
    buffer[word_len - 1] = '\0';
    word_len--;
  }
  char* word;
  while (line) {  // line is not NULL
    // double the dictionary size if it's full
    if (word_count == dict_size) {
      dict_size *= 2;
      dict = (Dictionary) realloc(dict, dict_size * 2);
    }
    // save the word in a new allocated space and put it into the dictionary
    word = malloc(sizeof(char) * word_len);
    strncpy(word, buffer, word_len + 1);
    dict[word_count] = word;

    // go to the next line
    line = fgets(buffer, buffer_len, input);
    word_len = strlen(buffer);
    if (buffer[word_len - 1] == '\n') {
      word_len--;
      buffer[word_len] = '\0';
    }
    word_count++;
  }

  // assign to output parameter
  *dict_result = dict;

  // clean up
  free(buffer);
  return word_count;
}

void free_dictionary(Dictionary dict, size_t size) {
  // To free the dictionary, we need to free the block allocated to every word
  for (size_t i = 0; i < size; i++) {
    free(dict[i]);
  }
}

int check_spelling(Dictionary dict, size_t size, char* word) {
  int lo = 0, hi = size - 1;
  int mid;
  int cmp_result;

  // typical binary search
  do {
    mid = (lo + hi) / 2;
    cmp_result = strcmp(word, dict[mid]);
    if (cmp_result == 0) {
      return 1;
    } else if (cmp_result > 0) {
      lo = mid + 1;
    } else {
      hi = mid - 1;
    }
  } while (lo <= hi);

  // didn't find a match
  return 0;
}
