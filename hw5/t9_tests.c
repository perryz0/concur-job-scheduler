#include <string.h>

#include "safe_assert.h"
#include "t9_lib.h"

void AssertReturnedStringEquals(char* expected, char* actual);
T9* initializeTinyDict();

suite("T9") {
  test("Empty initialization") {
    T9* dict = InitializeEmptyT9();
    safe_assert(dict != NULL);
    DestroyT9(dict);
  }

  test("Add words to T9 dictionary and singular prediction") {   // Renamed
    T9* dict = InitializeEmptyT9();
    safe_assert(dict != NULL);

    AddWordToT9(dict, "book");
    AddWordToT9(dict, "cool");

    char* word = PredictT9(dict, "2665#");
    AssertReturnedStringEquals("cool", word);

    DestroyT9(dict);
  }

  test("Add more words to T9 dictionary") {
    T9* dict = InitializeEmptyT9();
    safe_assert(dict != NULL);

    AddWordToT9(dict, "good");
    AddWordToT9(dict, "home");
    AddWordToT9(dict, "gone");
    AddWordToT9(dict, "hood");

    char* word1 = PredictT9(dict, "4663");
    char* word2 = PredictT9(dict, "4663#");
    char* word3 = PredictT9(dict, "4663##");
    char* word4 = PredictT9(dict, "4663###");
    AssertReturnedStringEquals("good", word1);
    AssertReturnedStringEquals("home", word2);
    AssertReturnedStringEquals("gone", word3);
    AssertReturnedStringEquals("hood", word4);

    DestroyT9(dict);
  }

  test("Initialize from file") {
    T9* dict = InitializeFromFileT9("small_dictionary.txt");
    safe_assert(dict != NULL);
    DestroyT9(dict);
  }

  test("Predict word with single digit sequence") {
    T9* dict = InitializeEmptyT9();
    safe_assert(dict != NULL);

    AddWordToT9(dict, "a");
    AddWordToT9(dict, "b");

    char* word1 = PredictT9(dict, "2");
    char* word2 = PredictT9(dict, "2#");
    AssertReturnedStringEquals("a", word1);
    AssertReturnedStringEquals("b", word2);
  }

  test("Predict word with no actual matches") {
    T9* dict = initializeTinyDict();

    char* word = PredictT9(dict, "2232323232");
    safe_assert(word == NULL);
  
    DestroyT9(dict);
  }

  test("Predict word with empty sequence") {
    T9* dict = initializeTinyDict();

    char* word = PredictT9(dict, "");
    safe_assert(word == NULL);
  
    DestroyT9(dict);
  }

  test("Predict word with NULL sequence") {
    T9* dict = initializeTinyDict();

    char* word = PredictT9(dict, NULL);
    safe_assert(word == NULL);
  
    DestroyT9(dict);
  }

  test("Predict word with non-numerical sequence") {
    T9* dict = initializeTinyDict();

    char* word = PredictT9(dict, "1aaa");
    safe_assert(word == NULL);
  
    DestroyT9(dict);
  }

  test("Predict word with invalid pound usage") {
    T9* dict = InitializeFromFileT9("small_dictionary.txt");
    safe_assert(dict != NULL);


    char* word = PredictT9(dict, "2665#2");
    safe_assert(word == NULL);
  
    DestroyT9(dict);
  }

  test("Predict word with sequence containing 1") {
    T9* dict = InitializeFromFileT9("small_dictionary.txt");
    safe_assert(dict != NULL);

    char* word = PredictT9(dict, "2615");
    safe_assert(word == NULL);
  
    DestroyT9(dict);
  }

  test("Predict word with sequence containing 0") {
    T9* dict = InitializeFromFileT9("small_dictionary.txt");
    safe_assert(dict != NULL);


    char* word = PredictT9(dict, "2605");
    safe_assert(word == NULL);
  
    DestroyT9(dict);
  }


}

void AssertReturnedStringEquals(char* expected, char* actual) {
  safe_assert(actual > 0);
  safe_assert(strlen(actual) == strlen(expected));
  safe_assert(strcmp(actual, expected) == 0);
}

T9* initializeTinyDict() {
  T9* dict = InitializeEmptyT9();
  safe_assert(dict != NULL);
 
  AddWordToT9(dict, "book");
  AddWordToT9(dict, "cool");

  return dict;
}
