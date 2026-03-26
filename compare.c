#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>

//Initialization

    struct word {   
        char *name;         //The word itself
        int count;          //The count of said word
        double frequency;        //The frequency of said word
    };

    struct fileData{
        char *name;         //The filename
        struct word *words; //The array containing word structs
        int uniqueWords;    //Total unique words
        int totalWords;     //Total words 
        int capacity;       //Room we have before realloc
    };

//Helper Functions

    //Uses binary search to find word insertion point
    /*
        Base case: No items in file.words, so we just insert
        Algorithm: Run strcmp() on median
            If strcmp returns 0, add 1 to that word's count and totalWords, return
            Else if strcmp returns -1, recurse with upper = med-1
            Else if strcmp returns 1, recurse with lower = med+1
            Else if word not found, increase capacity if needed and shift elements + insert
        Expected insert time: O(n) for shifting all words to the right worst case, best case we find the word and count++ so O(logn)
        Expected overall runtime: O(n^2) worst, O(nlogn) best
    */
    void insert(struct fileData *file, char *newWordName) {
        //Initial Variables, adding 1 to totalWords since we insert
        file->totalWords++;
        int low = 0;
        int high = file->uniqueWords-1;
        int med = 0;
        int cmp = 0;

        //Binary Search - we find the word
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
            }
            else if (cmp < 0) {
                high = med - 1;
            }
            else {
                low = med + 1;             
            }
        }

        //Unique Word - first we check if capacity is large enough
        if (file->uniqueWords >= file->capacity) {
            //newCapacity setup
            int newCapacity = 0;
            if (file->capacity == 0) newCapacity = 10;
            else newCapacity = file->capacity * 2;

            //realloc and error checking
            struct word *temp = realloc(file->words, newCapacity * sizeof(struct word));
            if (!temp) {
                perror("realloc");
                exit(EXIT_FAILURE);
            }

            //variable updating
            file->words = temp;
            file->capacity = newCapacity;
        }

        //Unique Word - then we shift (if not at end) and insert 
        /*
            We use low to be our insertion point, as the word before is guaranteed cmp > 0
            the word at low is also guaranteed cmp < 0, and thus we shift [low ... uniqueWords] right one word
            I hope this writing makes sense to the reader
        */
        if (low < file->uniqueWords) memmove(&file->words[low + 1], &file->words[low], (file->uniqueWords - low) * sizeof(struct word));
        file->words[low].name = newWordName;
        file->words[low].count = 1;
        file->words[low].frequency = 0.0;
        file->uniqueWords++;
    }

    //Creates the fileData struct for one file
    //NOTE: MAKE SURE WORD PASSED TO INSERT IS LOWERCASE
    struct fileData create(char *path) {
        struct fileData file;
            file.name = path;
            file.uniqueWords = 0;
            file.totalWords = 0;

        int fd = open(path, O_RDONLY);



        return file;
    }

    //Calculates Word Frequency Distribution
    int wfd(struct fileData file) {
        
    } 

    //Calculates Jenson-Shannon Distance
    int jsd(struct fileData file) {

    }

//Main

    int main(int argc, char **argv) {
        //Run a for loop for all args
            //Recursively search for text files then create filedata struct for all and yadda yadda
            //I think we check if dir first using opendir, and if null use create
            //Be sure to skip dotfiles (files that start with ".")
        //We would have n choose 2 comparisons total
            //My opinion on comparisons: may be best to do nested for loop where
            //for i=0 to n, for j=i+1 to n
            //to compare every single one with each other
        //I think the function call itself also counts as an arg iirc so skip that but I could be wrong
    }