#pragma once
#include<stdio.h>
#include"stack.h"

void getStr(char** str, FILE* text);

char* memoryForWord(const char* word_for_memory);

int findSizeOfWOrd(const char* str, int* index);

char* wordCopy(const char* str, int index, int size);

void takeWordsFromString(FILE* text, Node_t** head);

void findWordsAmount(Node_t** head);


int findProfit(const Node_t* head_long_word, const Node_t* head_short_word);

int findShortWord(const Node_t* head_long, Node_t* head_short, int* profit, int* cheker);

int findPlacesOfWordsAndProfit(Node_t* head_long, Node_t* head_short, int* place_long_word, int* place_short_word);

int chekerForProfit(int size_long_word, int size_short_word, int profit);