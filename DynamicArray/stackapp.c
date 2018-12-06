/*************************************
 * **Author: Mathew McDade
 * **Date: Fri Oct  6 20:23:12 PDT 2017 
 * **Desription: completion of assigned program to check whether a given string has balanced
 * brackets and braces using a dynamic stack implementation based on the provided skeleton code.
 * *************************************/

/*	stack.c: Stack application. */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "dynArray.h"


/* ***************************************************************
Using stack to check for unbalanced parentheses.
***************************************************************** */

/* Returns the next character of the string, once reaches end return '0' (zero)
	param: 	s pointer to a string 	
	pre: s is not null		
*/
char nextChar(char* s)
{
	static int i = -1;	
	char c;
	++i;	
	c = *(s+i);			
	if ( c == '\0' )
		return '\0';	
	else 
		return c;
}

/* Checks whether the (), {}, and [] are balanced or not
	param: 	s pointer to a string 	
	pre: s is not null	
	post:	
*/
int isBalanced(char* s)
{
	/* FIXED: You will write this function */
    assert(s);
    DynArr *parenArr = newDynArr(8);
    DynArr *braceArr = newDynArr(8);
    DynArr *brackArr = newDynArr(8);
    char i;
    while((i = nextChar(s)) && (i!='\0')) {
        /*printf("%c\n",i);*/
        if(i=='(') {
            addDynArr(parenArr, i);
        }
        if(i==')' && !isEmptyDynArr(parenArr)) {
            popDynArr(parenArr);
        }
        else if(i==')' && isEmptyDynArr(parenArr)) {
            deleteDynArr(parenArr);
            deleteDynArr(braceArr);
            deleteDynArr(brackArr);
            return 0;
        }
        if(i=='{') {
            addDynArr(braceArr, i);
        }
        if(i=='}' && !isEmptyDynArr(braceArr)) {
            popDynArr(braceArr);
        }
        else if(i=='}' && isEmptyDynArr(braceArr)) {
            deleteDynArr(parenArr);
            deleteDynArr(braceArr);
            deleteDynArr(brackArr);
            return 0;
        }
        if(i=='[') {
            addDynArr(brackArr, i);
        }
        if(i==']' && !isEmptyDynArr(brackArr)) {
            popDynArr(brackArr);
        }
        else if(i==']' && isEmptyDynArr(brackArr)) {
            deleteDynArr(parenArr);
            deleteDynArr(braceArr);
            deleteDynArr(brackArr);
            return 0;
        }
    }
    if(!isEmptyDynArr(parenArr)) {
        deleteDynArr(parenArr);
        deleteDynArr(braceArr);
        deleteDynArr(brackArr);
        return 0;
    }
    if(!isEmptyDynArr(braceArr)) {
        deleteDynArr(parenArr);
        deleteDynArr(braceArr);
        deleteDynArr(brackArr);
        return 0;
    }
    if(!isEmptyDynArr(brackArr)) {
        deleteDynArr(parenArr);
        deleteDynArr(braceArr);
        deleteDynArr(brackArr);
        return 0;
    }
    deleteDynArr(parenArr);
    deleteDynArr(braceArr);
    deleteDynArr(brackArr);
    return 1;
}

int main(int argc, char* argv[]){
	
	char* s=argv[1];	
	int res;
	
	printf("Assignment 2\n");

	res = isBalanced(s);

	if (res)
		printf("The string %s is balanced\n",s);
	else 
		printf("The string %s is not balanced\n",s);
	
	return 0;	
}

