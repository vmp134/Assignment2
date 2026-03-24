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
        double freq;        //The frequency of said word
    };

    struct fileData{
        char *name;         //The filename
        struct word *words; //The array containing word structs
        int wordCount;      //Total unique words
        int allWords;       //Total words 
    };

//Helper Functions

    //Uses binary search to find word insertion point
    /*
        Base case: No items in file.words, so we just insert
        Algorithm: Run strcmp() on median
        If strcmp returns 0, add 1 to that word's frequency and allwords, break
        Else if strcmp returns -1, recurse with upper = med-1
        Else if strcmp returns 1, recurse with lower = med+1
        Else if word not found, WORK NEEDED
        Expected runtime: O(log(n))
    */
    //NOTE: As of 3/23, I've realized if we have an array like this, we would need to move EVERY word up one space if we wanna insert.
    //This yields us O(n) for each movement phase, for EACH WORD. O(n^2) worst case. This is the same as the linked list approach.
    //This is inefficient, and I think we'll do the following:
    /*
        Use an array "Words" to find words
            append each word to the array regardless of uniqueness
            sort the array so identical words are next to each other in O(nlogn)
            Condense identical words into one word struct, which is an O(n) walkthrough 
            Overall, should be O(nlogn), but uses more memory
    */
    /*
    void insert(struct fileData file, struct word x) {
        if (file.wordCount == 0) {
            file.words[0] = x;
            file.wordCount++;
            file.allWords++;
            return;        
        }
        
        int low = 0;
        int high = file.wordCount;
        int med = (high + low) / 2;

        while (low <= high) {
            int c = strcmp(x.name, file.words[med].name);
            if (c == 0) {

            }
            else if (c < 0) {

            }
            else if (c > 0) {
                
            }
        }
    }
    */
    

    //Creates the fileData struct for one file
    struct fileData create(char *path) {
        struct fileData ret;
            ret.name = path;
            ret.wordCount = 0;
            ret.allWords = 0;

        int fd = open(path, O_RDONLY);



        return ret;
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
        //I think the function call itself also counts as an arg iirc so skip that
    }