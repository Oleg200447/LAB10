#pragma once
#include<stdio.h>

typedef struct Word_change {
    char* word_long;
    char* word_short;
    struct Word_change* next;
}Word_c;


void pushWord(Word_c** head, char* word_long, char* word_short);

void freeStackWord(Word_c** head);




char* memoryForWord(char* word_for_memory);

char* wordCopy(char* str, int index, int size);

int findSizeOfWOrd(char* str, int* index);

void makeStackOfWords(Word_c** head);

char* takeWordsFromString(char* str,int *pos_in_str);

void getStr(char** str, FILE* text);


void findSpecSymbol(FILE* text);

void takeInfo(Word_c** head, FILE* text);


void decompression(Word_c* list);