#include "Header.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FIRST_TIME_MEET 1
#define EQUAL 0

void pushWord(Word_c** head, char* word_long, char* word_short) {
    Word_c* storer = malloc(sizeof(Word_c));
    if (storer == NULL) {
        exit(EXIT_FAILURE);
    }
    storer->next = *head;
    storer->word_long = memoryForWord(word_long);
    storer->word_long = word_long;
    storer->word_short = memoryForWord(word_short);
    storer->word_short = word_short;
    *head = storer;
}

void freeStackWord(Word_c** head)
{
    while (*head)
    {
        Word_c* tmp = *head;
        free((*head)->word_long);
        free((*head)->word_short);
        *head = (*head)->next;
        free(tmp);
    }
}
