// Reads the next word in LOWERCASE from the given stream into buf. A valid
// word consists of entirely alpha characters, or a single '\n' character if
// two consecutive \n are found in the stream. All other bytes that come before
// a word is skipped and consumed after this operation. In the case where EOF is
// reached before a word, buf will be set to an empty string.
//
// Note: Utils.h and Utils.c are guaranteed to have the correct behavior as
//       documented so you don't have to debug this, but feel free to take a
//       look if you'd like.
//
// YOU MAY NOT CHANGE THE CONTENT OF THIS FILE.
//

#ifndef UTILS
#define UTILS


// params:
//     buf:      buffer to store the word
//     buf_size: size of the buffer, i.e. the maximum number of bytes to write
//     stream:   stream to read from
void get_word(char* buf, int buf_size, FILE* stream);

#endif  // UTILS
