// This file contains the definition for the file parsing utility functions.
// Again, the content of this file is guaranteed to be correct.
//
// YOU MAY NOT CHANGE THE CONTENT OF THIS FILE.

#include <ctype.h>
#include <stdio.h>

// Consumes all leading bytes in the stream that are not '\n' or alpha
// characters in the given stream.
static void skip_to_alpha_or_newline(FILE* stream);

void get_word(char* buf, int buf_size, FILE* stream) {
  int c;  // a character
  int index = 0;

  // reads from stream to buffer
  skip_to_alpha_or_newline(stream);
  c = fgetc(stream);

  if (c != EOF) {
    buf[index] = tolower(c);
    index++;
    if (index == buf_size) {  // when the buf_size is only 2
      return;
    } else if (c == '\n') {  // special case for \n
      skip_to_alpha_or_newline(stream);
      c = fgetc(stream);
      if (c == '\n') {  // consecutive newlines
        buf[index] = '\0';
        return;
      } else {
        // roll back the index so we can read the word after the single \n
        index--;
        ungetc(c, stream);
      }
    }

    // reads the actual word
    do {
      c = fgetc(stream);
      if (!isalpha(c)) {
        buf[index] = '\0';
        ungetc(c, stream);
        return;
      } else {
        buf[index] = tolower(c);
      }
      index++;
    } while (index < buf_size);

  } else {
    buf[index] = '\0';
  }
}

void skip_to_alpha_or_newline(FILE* stream) {
  int c;

  do {
    c = fgetc(stream);
  } while (!isalpha(c) && c != '\n' && c != EOF);  // stops at alpha or \n

  // put back the extra character we read
  // does no change to the stream if c == EOF
  ungetc(c, stream);
}
