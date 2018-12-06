/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Mathew McDade
 * Date: 11/20/2017 6:17:34 PM
 */

#include "hashMap.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <assert.h>

/**
 * Allocates a string for the next word in the file and returns it. This string
 * is null terminated. Returns NULL after reaching the end of the file.
 * @param file
 * @return Allocated string or NULL.
 */
char* nextWord(FILE* file)
{
    int maxLength = 16;
    int length = 0;
    char* word = malloc(sizeof(char) * maxLength);
    while (1)
    {
        char c = fgetc(file);
        if ((c >= '0' && c <= '9') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'a' && c <= 'z') ||
            c == '\'')
        {
            if (length + 1 >= maxLength)
            {
                maxLength *= 2;
                word = realloc(word, maxLength);
            }
            word[length] = c;
            length++;
        }
        else if (length > 0 || c == EOF)
        {
            break;
        }
    }
    if (length == 0)
    {
        free(word);
        return NULL;
    }
    word[length] = '\0';
    return word;
}

/**
 * Prints the concordance of the given file and performance information. Uses
 * the file input1.txt by default or a file name specified as a command line
 * argument.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, const char** argv)
{
    // FIXED: implemented concordance using hashMap.c
    const char *fileName = "input1.txt";
    if (argc > 1)
    {
        fileName = argv[1];
    }
    printf("Opening file: %s\n", fileName);
    
    clock_t timer = clock();
    
    HashMap* map = hashMapNew(10);
    
    // --- Concordance code begins here ---
    FILE *input_file = fopen(fileName, "r");
    if(!input_file) {
        fprintf(stderr, "Cannot open input file %s.\n",fileName);
        return 0;
    }

    char *currentWord = nextWord(input_file);
    while(currentWord) {
        if(hashMapContainsKey(map,currentWord)) {
            int *count = (hashMapGet(map,currentWord));
            (*count)++;
        }
        else {
            hashMapPut(map,currentWord,1);
        }
        free(currentWord);
        currentWord = nextWord(input_file);
    }
    fclose(input_file);
    // Be sure to free the word after you are done with it here.
    // --- Concordance code ends here ---
    printf("\n");
    for (int i = 0; i < map->capacity; i++)
    {
        HashLink* link = map->table[i];
        while(link) {
            printf("%-11s:-------%d\n",link->key,link->value);
            link = link->next;
        }
    }
    printf("\n");
    
    hashMapPrint(map);
    
    timer = clock() - timer;
    printf("\nRan in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    printf("Empty buckets: %d\n", hashMapEmptyBuckets(map));
    printf("Number of links: %d\n", hashMapSize(map));
    printf("Number of buckets: %d\n", hashMapCapacity(map));
    printf("Table load: %f\n", hashMapTableLoad(map));
    
    hashMapDelete(map);
    return 0;
}