/*
 * CS 261 Assignment 5
 * Name: Mathew McDade
 * Date: 11/13/2017
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[FORMAT_LENGTH];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
     while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    // FIXED: Implement
    assert(list);

    switch(command)
    {
        case 'l': {
            printf("Please enter filename to load:\n");
            char fileName[128];
            scanf("%[^\n]s",fileName);
            while(getchar()!='\n');
            fflush(stdout);
            FILE *input_file = fopen(fileName,"r");
            if(input_file==NULL) {
                fprintf(stderr, "Cannot open input file %s.\n",fileName);
            }
            else {
                listLoad(list,input_file);
                fclose(input_file);
                printf("The list has been loaded from file successfully.\n\n");
            }
            break; }
        case 's': {
            printf("Please enter filename to save:\n");
            char fileName[128];
            scanf("%[^\n]s",fileName);
            while(getchar()!='\n');
            FILE *output_file = fopen(fileName, "w");
            if(output_file==NULL) {
                fprintf(stderr, "Cannot open output file %s.\n",fileName);
            }
            else {
                listSave(list,output_file);
                fclose(output_file);
                printf("The list has been saved to the file successfully.\n\n");
            }
            break; }
        case 'a': {
            int priority;
            char task[128];
            printf("Please enter task description?\n");
            scanf("%[^\n]s",task);
            printf("Please enter task priority (0(highest)-999(lowest)):\n");
            scanf("%d",&priority);
            while(getchar()!='\n');

            Task *temp = taskNew(priority,task);

            dyHeapAdd(list,temp,taskCompare);
            printf("The task '%s' has been added to your to-do list.\n\n",task);
            break; }
        case 'g': {
            if(dySize(list)==0) {
                printf("Your to-do list is empty!\n");
            }
            else {
                printf("Your first task is:\n");
                taskPrint(dyHeapGetMin(list));
            }
            printf("\n\n");
            break; }
        case 'r': {
            if(dySize(list)==0) {
                printf("Your to-do list is empty!\n");
            }
            else {
                printf("Your first task:\n");
                taskPrint(dyHeapGetMin(list));
                printf("\nhas been removed from the list.\n");
                struct Task *toDelete = dyHeapGetMin(list);
                dyHeapRemoveMin(list,taskCompare);
                taskDelete(toDelete);
            }
            printf("\n");
            break; }
        case 'p': {
            printf("Your List:\n");
            listPrint(list);
            printf("\n");
            break; }
        case 'e': {
            printf("Bye!\n\n");
            break; }
        default: ;
    }
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
 /* free dynamically allocated List pointers in array to avoid memory leaks */
         /* Fix it */

    for(int i=0;i<dySize(list);i++) {
        Task *toDelete = dyGet(list,i);
        taskDelete(toDelete);
    }
    dyDelete(list);
    return 0;
}