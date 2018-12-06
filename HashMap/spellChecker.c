/*
 * CS 261 Data Structures
 * Assignment 5
 * Name: Mathew McDade
 * Date: 11/20/2017 6:23:55 PM
 */

#include "hashMap.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
 * Loads the contents of the file into the hash map.
 * @param file
 * @param map
 */
void loadDictionary(FILE* file, HashMap* map)
{
    // FIXED: implemented function to hash each word from a dictionary file and add it to a map.
    char *currentWord = nextWord(file);

    while(currentWord) {
        hashMapPut(map,currentWord,0);
        free(currentWord);
        currentWord = nextWord(file);
    }
    free(currentWord);
}

/*********Levenshtein distance code adapted from: https://rosettacode.org/wiki/Levenshtein_distance#C ***********/
//The Levenshtein distance is used to determine the edit distance between two strings. This is useful for selecting
//recommendations in the spellchecker program.

int levenshtein(const char *s,const char *t) {
    int sLength = strlen(s);
    int tLength = strlen(t);
    int dMatrix[sLength+1][tLength+1];
    for(int i=0;i<=sLength;i++) {
        for(int j=0;j<=tLength;j++) {
            dMatrix[i][j] = -1;
        }
    }
    int distance(int i, int j) {
        if(dMatrix[i][j]>=0) {
            return dMatrix[i][j];
        }
        int x;
        if(i==sLength)
            x = tLength - j;
        else if(j==tLength)
            x = sLength - i;
        else if(s[i]==t[j])
            x = distance(i+1,j+1);
        else {
            x = distance(i+1,j+1);
            int y;
            if((y = distance(i,j+1))<x || (y = distance(i+1,j))<x)
                x = y;
            x++;
        }
        return dMatrix[i][j] = x;
    }
    return distance(0,0);
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
    // FIXED: implemented a spellchecker that checks whether a given word is present in the dictionary and, if not,
    // uses the Levenshtein distance between the user input word and each dictionary word to provide recommendations.
    HashMap* map = hashMapNew(1000);
    
    FILE* dictionary_file = fopen("dictionary.txt", "r");
    if(!dictionary_file) {
        fprintf(stderr, "Cannot open dictionary.\n");
        return 0;
    }
    clock_t timer = clock();
    loadDictionary(dictionary_file, map);
    timer = clock() - timer;
    printf("Dictionary loaded in %f seconds\n", (float)timer / (float)CLOCKS_PER_SEC);
    fclose(dictionary_file);
    
    char inputBuffer[256];
    int quit = 0;
    while (!quit)
    {
        printf("Enter a word or \"quit\" to quit: ");
        scanf("%s", inputBuffer);

        // Implement the spell checker code here..
        int recDistance;
        if(strlen(inputBuffer)<=6) {
            recDistance = 2;
        }
	   else if(strlen(inputBuffer)<10) {
		   recDistance = 3;
	   }
        else {
            recDistance = 4;
        }
	   printf("rD:%d\n\n",recDistance);

        if(hashMapContainsKey(map,inputBuffer)) {
            printf("The word '%s' is spelled correctly.\n\n",inputBuffer);
        }
        else {
            printf("Did you mean:\n");

            for (int i = 0; i < map->capacity; i++)
            {
                HashLink* currentLink = map->table[i];
                while (currentLink) {
                    if(levenshtein(inputBuffer,currentLink->key)<recDistance) {
                        printf("%s\n",currentLink->key);
                    }
                    currentLink = currentLink->next;
                }
            }
            printf("\n");
        }

        if (strcmp(inputBuffer, "quit") == 0)
        {
            printf("Quitting...\n\n");
            quit = 1;
        }
    }
    
    hashMapDelete(map);
    return 0;
}
