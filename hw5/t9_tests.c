#include <string.h>

#include "safe_assert.h"
#include "t9_lib.h"

void AssertReturnedStringEquals(char* expected, char* actual);

suite("T9") {
  test("Empty initialization") {
    T9* dict = InitializeEmptyT9();
    safe_assert(dict != NULL);
    DestroyT9(dict);
  }

  test("Rename me! What is this test testing?") {
    T9* dict = InitializeEmptyT9();
    safe_assert(dict != NULL);

    AddWordToT9(dict, "book");
    AddWordToT9(dict, "cool");

    char* word = PredictT9(dict, "2665#");
    AssertReturnedStringEquals("cool", word);

    DestroyT9(dict);
  }
}

void AssertReturnedStringEquals(char* expected, char* actual) {
  safe_assert(actual > 0);
  safe_assert(strlen(actual) == strlen(expected));
  safe_assert(strcmp(actual, expected) == 0);
}
