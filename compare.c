#include <dirent.h>
#include <fcntl.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFERLENGTH 4096

// Initialization

struct word {
  char *name;       // The word itself
  int count;        // The count of said word
  double frequency; // The frequency of said word
};

struct fileData {
  char *name;         // The filename
  struct word *words; // The array containing word structs
  int uniqueWords;    // Total unique words
  int totalWords;     // Total words
  int capacity;       // Room we have before realloc
};

// Helper Functions

// Uses binary search to find word insertion point
/*
    Base case: No items in file.words, so we just insert
    Algorithm: Run strcmp() on median
        If strcmp returns 0, add 1 to that word's count and totalWords, return
        Else if strcmp returns -1, recurse with upper = med-1
        Else if strcmp returns 1, recurse with lower = med+1
        Else if word not found, increase capacity if needed and shift elements +
   insert Expected insert time: O(n) for shifting all words to the right worst
   case, best case we find the word and count++ so O(logn) Expected overall
   runtime: O(n^2) worst, O(nlogn) best
*/
void insert(struct fileData *file, char *newWordName) {
  // Initial Variables, adding 1 to totalWords since we insert
  file->totalWords++;
  int low = 0;
  int high = file->uniqueWords - 1;
  int med = 0;
  int cmp = 0;

  // Binary Search - we find the word
  /*
      Of note: if we can't find the word, we will end up with
          low = high + 1
      As we get to the insertion point around med,
          low will be 1 above the last cmp > 0
          high will be 1 below the last cmp < 0
      Insertion point should be the space between, which doesn't exist yet
  */
  while (low <= high) {
    med = low + ((high - low) / 2);
    cmp = strcmp(newWordName, file->words[med].name);

    if (cmp == 0) {
      file->words[med].count++;
      free(newWordName);
      return;
    } else if (cmp < 0) {
      high = med - 1;
    } else {
      low = med + 1;
    }
  }

  // Unique Word - first we check if capacity is large enough
  if (file->uniqueWords >= file->capacity) {
    // realloc and error checking
    struct word *temp =
        realloc(file->words, file->capacity * 2 * sizeof(struct word));
    if (!temp) {
      perror("realloc");
      exit(EXIT_FAILURE);
    }

    // variable updating
    file->words = temp;
    file->capacity *= 2;
  }

  // Unique Word - then we shift (if not at end) and insert
  /*
      We use low to be our insertion point, as the word before is guaranteed cmp
     > 0 the word at low is also guaranteed cmp < 0, and thus we shift [low ...
     uniqueWords] right one word I hope this writing makes sense to the reader
  */
  if (low < file->uniqueWords)
    memmove(&file->words[low + 1], &file->words[low],
            (file->uniqueWords - low) * sizeof(struct word));
  file->words[low].name = newWordName;
  file->words[low].count = 1;
  file->words[low].frequency = 0.0;
  file->uniqueWords++;
}

// Creates the fileData struct for one file
/*
    NOTE: MAKE SURE WORD PASSED TO INSERT IS LOWERCASE

    What we'll do is just have a string that we keep pushing chars into and pop
   if we see a space call insert() on the word found and loop until EOF Since we
   are checking for spaces to pop, we need to see if file did not end in space
   to get last word we're not using an actual stack I'm just saying push and pop
   because same logic
*/
struct fileData *create(char *path) {
  // fileData initialization
  struct fileData *file = malloc(sizeof(struct fileData));
  file->name = strdup(path);
  file->uniqueWords = 0;
  file->totalWords = 0;
  file->capacity = 10;
  file->words = malloc(10 * sizeof(struct word));

  // File variables
  char buf[BUFFERLENGTH];
  char *temp = malloc(64*sizeof(char));
  size_t bytesRead;
  int fd = open(path, O_RDONLY);

  // Read Loop
  for (int i = 0; read(fd, buf, BUFFERLENGTH) /*NOT COMPLETE*/; i += BUFFERLENGTH) {

  }

  // Final Word Check


  return file;
}

//Frees memory for unused fileData structs
int destroy(struct fileData *file) {
  for (int i = 0; i < file->uniqueWords; i++) {
    free(file->words[i].name);
  }
  free(file->words);
  free(file->name);
  free(file);
}

// Calculates Word Frequency Distribution
void wfd(struct fileData *file) {
  for (int i = 0; i < file->uniqueWords; i++) {
    file->words[i].frequency = (double)file->words[i].count / file->totalWords;
  }
}
// Calculates Jenson-Shannon Distance
double jsd(struct fileData *f1, struct fileData *f2) {
  double kld1 = 0.0, kld2 = 0.0;
  int i = 0, j = 0;

  while (i < f1->uniqueWords && j < f2->uniqueWords) {
    int cmp = strcmp(f1->words[i].name, f2->words[j].name);

    if (cmp == 0) {
      double freq1 = f1->words[i].frequency;
      double freq2 = f2->words[j].frequency;
      double mean = (freq1 + freq2) / 2.0;
      kld1 += freq1 * log2(freq1 / mean);
      kld2 += freq2 * log2(freq2 / mean);
      i++;
      j++;
    } else if (cmp < 0) {
      // word only in f1, mean = freq1/2, log2(freq1 / (freq1/2)) = log2(2) = 1
      kld1 += f1->words[i].frequency;
      i++;
    } else {
      kld2 += f2->words[j].frequency;
      j++;
    }
  }

  // drain remaining words
  while (i < f1->uniqueWords) {
    kld1 += f1->words[i].frequency;
    i++;
  }
  while (j < f2->uniqueWords) {
    kld2 += f2->words[j].frequency;
    j++;
  }

  return sqrt(0.5 * kld1 + 0.5 * kld2);
}

// Main
/*
Run a for loop for all args
Recursively search for text files then create filedata struct for all and yadda
yadda I think we check if dir first using opendir, and if null use create Be
sure to skip dotfiles (files that start with ".") We would have n choose 2
comparisons total My opinion on comparisons: may be best to do nested for loop
where for i=0 to n, for j=i+1 to n to compare every single one with each other
I think the function call itself also counts as an arg iirc so skip that but I
could be wrong

p2.pdf: Comparisons are printed in decreasing order of combined word count (that is, the total number of words in both files).
*/
int main(int argc, char **argv) {
  //File Search
  int totalFiles = argc;
  char *path = "";
  for (int i = 1; i < totalFiles; i++) {
    path = argv[i];
  }
  struct fileData **files = malloc(totalFiles * sizeof(struct fileData));
  

  //Comparison loop
  for (int i = 0; i < totalFiles; i++) {
    for (int j = i+1; j < totalFiles; j++) {

    }
  }

  //Memory Cleanup
  for (int i = 0; i < totalFiles; i++) {
    destroy(files[i]);
  }
  free(files);

  return EXIT_SUCCESS;
}
