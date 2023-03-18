#pragma once
#include<stdio.h>
#include"stack.h"

void compression(Word_c* list);

void addLibrary(Word_c* list, FILE* text_compr);

char* changeOneStr(char** str, Word_c* list);

void changePairOneString(char** str, Word_c* pair);

void changeWord(char** str, const Word_c* pair, const char* word, int* end_word);


char* makeSymbol();

char* makeString(const Word_c* list);

void addWordToString(char** str, const char* word, int* counter);