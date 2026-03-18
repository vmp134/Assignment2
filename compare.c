#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

struct {   
    char *name;         //The word itself
    double freq;        //The frequency of said word
} word;

struct {
    char *name;         //The filename
    word *words;        //The array containing word structs
    int wordCount;      //Total unique words
    int allWords;       //Total words 
} fileData;





int wfd(char *file) {
    
} 

int jsd() {

}