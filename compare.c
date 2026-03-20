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
    void insert(struct fileData file, struct word x) {

    }

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