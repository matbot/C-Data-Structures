/*
 * CS 261 Assignment 5
 * Name: Mathew McDade
 * Date: 11/13/17
 */

#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

/**
 * Creates a new task with the given priority and name.
 * @param priority
 * @param name
 * @return  The new task.
 ***/
Task* taskNew(int priority, char* name)
{
    // FIXED: implement
    Task *t = malloc(sizeof(Task));
    assert(t);
    t->priority = priority;
    strcpy(t->name,name);

    return t;
}

/**
 * Frees a dynamically allocated task.
 * @param task
 */
void taskDelete(Task* task)
{
    free(task);
}

/**
 * Casts left and right to Task pointers and returns
 * -1 if left's priority < right's priority,
 *  1 if left's priority > right's priority,
 *  0 if left's priority == right's priority.
 * @param left  Task pointer.
 * @param right  Task pointer.
 * @return 
 */
int taskCompare(void* left, void* right)
{
    // FIXED: implement
    if(((Task*)left)->priority<((Task*)right)->priority) {
        return -1;
    }
    else if(((Task*)left)->priority>((Task*)right)->priority) {
        return 1;
    }
    else return 0;
}

/**
 * Prints a task as a (priority, name) pair.
 * @param value  Task pointer.
 */
void taskPrint(void* value)
{
    Task* task = (Task*)value;
    printf("Task: %-50s -------- Priority: %d",task->name,task->priority);
}
