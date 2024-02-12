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

  test("Add multiple words with same encoding and test predictions") {
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

    DestroyT9(dict);
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
    T9* dict = InitializeFromFileT9("dictionary.txt");
    safe_assert(dict != NULL);

    char* word = PredictT9(dict, "2665#2");
    safe_assert(word == NULL);
  
    DestroyT9(dict);
  }

  test("Predict word with sequence containing 1") {
    T9* dict = InitializeFromFileT9("dictionary.txt");
    safe_assert(dict != NULL);

    char* word = PredictT9(dict, "2615");
    safe_assert(word == NULL);
  
    DestroyT9(dict);
  }

  test("Predict word with sequence containing 0") {
    T9* dict = InitializeFromFileT9("dictionary.txt");
    safe_assert(dict != NULL);

    char* word = PredictT9(dict, "2605");
    safe_assert(word == NULL);
  
    DestroyT9(dict);
  }

  test("Predict word with sequence containing invalid asterisks") {
    T9* dict = InitializeFromFileT9("dictionary.txt");
    safe_assert(dict != NULL);

    char* word = PredictT9(dict, "2665*");
    safe_assert(word == NULL);
  
    DestroyT9(dict);
  }

  test("Predict word with sequence containing invalid chars") {
    T9* dict = InitializeFromFileT9("dictionary.txt");
    safe_assert(dict != NULL);


    char* word = PredictT9(dict, "2665%");
    safe_assert(word == NULL);
  
    DestroyT9(dict);
  }

  test("Add existing word into dictionary and it remains unchanged") {
    T9* dict = InitializeEmptyT9();
    safe_assert(dict != NULL);

    AddWordToT9(dict, "book");

    char* word_before = PredictT9(dict, "2665");
    safe_assert(word_before != NULL);

    AddWordToT9(dict, "book");
    
    char* word_after = PredictT9(dict, "2665");
    safe_assert(word_after != NULL);
    
    safe_assert(strcmp(word_before, word_after) == 0);

    DestroyT9(dict);
  }

  test("Check if all words are added into T9") {
    T9* dict = initializeTinyDict();
    safe_assert(dict != NULL);

    char* word1 = "book";
    char* word2 = "cool";
    
    char* pred1 = PredictT9(dict, "2665");
    char* pred2 = PredictT9(dict, "2665#");
    AssertReturnedStringEquals(pred1, word1);
    AssertReturnedStringEquals(pred2, word2);

    DestroyT9(dict);
  }

  test("Additional check if all words are added to T9") {
    T9* dict = initializeTinyDict();

    char* word1 = PredictT9(dict, "2665");
    char* word2 = PredictT9(dict, "2665#");
    safe_assert(word1 != NULL);
    safe_assert(word2 != NULL);
  
    DestroyT9(dict);
  }

  test("Check predictions when words are very similar in chars") {
    T9* dict = InitializeEmptyT9();
    safe_assert(dict != NULL);

    AddWordToT9(dict, "wor");
    AddWordToT9(dict, "work");
    AddWordToT9(dict, "works");
    AddWordToT9(dict, "wort");
    AddWordToT9(dict, "worker");
    AddWordToT9(dict, "worked"); 

    char* word1 = PredictT9(dict, "967");
    char* word2 = PredictT9(dict, "9675");
    char* word3 = PredictT9(dict, "96757");
    char* word4 = PredictT9(dict, "9678");
    char* word5 = PredictT9(dict, "967537");
    char* word6 = PredictT9(dict, "967533");
    AssertReturnedStringEquals("wor", word1);
    AssertReturnedStringEquals("work", word2);
    AssertReturnedStringEquals("works", word3);
    AssertReturnedStringEquals("wort", word4);
    AssertReturnedStringEquals("worker", word5);
    AssertReturnedStringEquals("worked", word6);

    DestroyT9(dict);
  }

  test("Checks if prediction returns NULL when digits come after pound") {
    T9* dict = initializeTinyDict();            // fix

    char* word1 = PredictT9(dict, "2665");
    char* word2 = PredictT9(dict, "2665#");
    char* word3 = PredictT9(dict, "2665#2");
    AssertReturnedStringEquals("book", word1);
    AssertReturnedStringEquals("cool", word2);
    safe_assert(word3 == NULL);
  
    DestroyT9(dict);
  }

  test("Predict word with multiple pound signs using passed dictionary") {
    T9* dict = InitializeFromFileT9("dictionary.txt");
    safe_assert(dict != NULL);

    char* word1 = PredictT9(dict, "2665");
    char* word2 = PredictT9(dict, "2665#");
    char* word3 = PredictT9(dict, "2665##");
    char* word4 = PredictT9(dict, "2665###");
    char* word5 = PredictT9(dict, "2665####");
    char* word6 = PredictT9(dict, "2665#####");
    char* word7 = PredictT9(dict, "2665######"); // should have no entry
    AssertReturnedStringEquals("amok", word1);
    AssertReturnedStringEquals("bonk", word2);
    AssertReturnedStringEquals("book", word3);
    AssertReturnedStringEquals("conk", word4);
    AssertReturnedStringEquals("cook", word5);
    AssertReturnedStringEquals("cool", word6);
    safe_assert(word7 == NULL);
  
    DestroyT9(dict);
  }

  test("Checks invalid for when nums only has pound or starts with pound") {
    T9* dict = InitializeFromFileT9("dictionary.txt");
    safe_assert(dict != NULL);

    char* word1 = PredictT9(dict, "#");
    char* word2 = PredictT9(dict, "####");
    char* word3 = PredictT9(dict, "###3232");
    char* word4 = PredictT9(dict, "#sdsda");
    safe_assert(word1 == NULL);
    safe_assert(word2 == NULL);
    safe_assert(word3 == NULL);
    safe_assert(word4 == NULL);
  
    DestroyT9(dict);
  }

  test("Check prediction with duplicate words, including invalid variants") {
    T9* dict = InitializeEmptyT9();
    safe_assert(dict != NULL);

    AddWordToT9(dict, "work");
    AddWordToT9(dict, "work");
    AddWordToT9(dict, "works");
    AddWordToT9(dict, "wor k");
    AddWordToT9(dict, "work ");
    AddWordToT9(dict, "work#"); 

    char* word1 = PredictT9(dict, "9675");
    char* word2 = PredictT9(dict, "9675#");
    char* word3 = PredictT9(dict, "96757");
    char* word4 = PredictT9(dict, "9675##");
    char* word5 = PredictT9(dict, "#9675");
    char* word6 = PredictT9(dict, "9675sd");
    AssertReturnedStringEquals("work", word1);
    safe_assert(word2 == NULL);
    AssertReturnedStringEquals("works", word3);
    safe_assert(word4 == NULL);
    safe_assert(word5 == NULL);
    safe_assert(word6 == NULL);

    DestroyT9(dict);
  }

  test("Check prediction with invalid upper case words") {
    T9* dict = InitializeEmptyT9();
    safe_assert(dict != NULL);

    AddWordToT9(dict, "WORK");
    char* word1 = PredictT9(dict, "9675");
    safe_assert(word1 == NULL);

    AddWordToT9(dict, "woRk");
    char* word2 = PredictT9(dict, "9675");
    safe_assert(word2 == NULL);

    AddWordToT9(dict, "work");
    char* word3 = PredictT9(dict, "9675");
    AssertReturnedStringEquals("work", word3);

    AddWordToT9(dict, "woRk");
    char* word4 = PredictT9(dict, "9675#");
    safe_assert(word4 == NULL);

    DestroyT9(dict);
  }

  test("Checks the middle words in a big dictionary") {     // Line ~40000
    T9* dict = InitializeFromFileT9("dictionary.txt");
    safe_assert(dict != NULL);

    char* word1 = PredictT9(dict, "5655");
    char* word2 = PredictT9(dict, "565533");
    char* word3 = PredictT9(dict, "565537");
    char* word4 = PredictT9(dict, "5655377");
    char* word5 = PredictT9(dict, "5655437##");
    char* word6 = PredictT9(dict, "5655464");
    char* word7 = PredictT9(dict, "56554767");
    char* word8 = PredictT9(dict, "565567");
    AssertReturnedStringEquals("loll", word1);
    AssertReturnedStringEquals("lolled", word2);
    AssertReturnedStringEquals("loller", word3);
    AssertReturnedStringEquals("lollers", word4);
    AssertReturnedStringEquals("lollies", word5);
    AssertReturnedStringEquals("lolling", word6);
    AssertReturnedStringEquals("lollipop", word7);
    AssertReturnedStringEquals("lollop", word8);
  
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
