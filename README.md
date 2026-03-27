0. Project Members
    Samuel Habib smh389, Victor Peng vmp134

1. Testing Plan


2. Design Notes
    - structure TODO (erase TODO and this text when done)
        Our project consists of the following structs to keep track of one file's data:
            struct word 
                char *name
                int count
                double frequency
            struct fileData 
                char *name
                struct word *words
                int uniqueWords
                int totalWords
                int capacity

        Here are our notes on the two:
            struct word
                Stores the name of the word, how many times it appears, and frequency.
            struct fileData
                Stores the name of the file, an array of word structs, total amount of unique words, total words, and the capacity of the struct word array.

        Our project performs the following in main():


    - insert()
        insert() uses binary search to find the correct insertion point of a word.
            insert() takes a fileData struct and the name of the word being inserted.
            This function ensures fileData.words remains alphabetically sorted.

        Cases
            Regardless of case, fileData.totalWords is incrememnted by 1.
            Case 1: The word exists in fileData:
                We increment word.count and fileData.totalWords.
            Case 2: The word does not exist:
                We check if our fileData has enough allocated memory.
                If not, we realloc to double capacity, and set capacity *= 2.
                We create the new word struct to hold our word, and increment fileData.uniqueWords and fileData.totalWords.

        We chose a dynamic array to avoid the cost of a struct word *next pointer per struct word for LinkedList.
            Instead of having an O(n) node traversal to find our word, we get an O(logn) find. 
            Unfortunately, we take the hit for inserting unique words. we must move a large portion of memory, rather than updating a *next pointer.
            This also gives us the freedom to search up any word, as we get indices instead of LinkedList pointer traversal. 

        Our expected runtime is:
            O(1), assuming binary search 

        insert() does not return, and exits upon a realloc failure. 

    - create() 
        create() initializes a new fileData struct for a given file.
            create() takes the path of the file.
            
            For each word in the file, create() calls insert().
        


        Upon completion, create() returns the fileData struct for a file, but has all word frequencies set to 0.0.    

    - destroy()
        destroy() frees up all memory used for one struct fileData. 

    - wfd()
        wfd() calculates the word frequency distribution of a file.
            wfd() takes a fileData struct.
            For each word in fileData.words, wfd() sets word.frequency = word.count/fileData.totalWords.

        Our expected runtime is O(n).

        Upon completion, wfd() does not return.

    - jsd() TODO
        