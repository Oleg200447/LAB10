#pragma once
#include<stdio.h>


typedef struct Node_tag {
    char* word;
    int amount;
    int size;
    enum Skip using;
    struct Node_tag* next;
} Node_t;


typedef struct Word_change {
    char* word_long;
    char* word_short;
    struct Word_change* next;
}Word_c;

enum Skip {
    USED,
    NO_USED
};


void pushAmount(Node_t** head, char* word,int amount);

void showStackAmount(const Node_t* head);

Node_t* popAmount(Node_t** head);

Node_t* chekerForWordInStack(Node_t* head, char* word);

void addWordInStack(Node_t** head, char* word);

void freeStackAmount(Node_t** head);

char* takeWordFromStack(Node_t* head, int place);



Word_c* popWord(Word_c** head);

void pushWord(Word_c** head, char* word_long, char* word_short);

void showStackWord(const Word_c* head);

void freeStackWord(Word_c** head);


void makeTwoStacks(Node_t** head, Node_t** head_long_words, Node_t** head_short_words);



void getStr(char** str, FILE* text);

char* memoryForWord(const char* word_for_memory);

int findSizeOfWOrd(const char* str, int* index);

char* wordCopy(const char* str, int index, int size);

void takeWordsFromString(FILE* text, Node_t** head);

void findWordsAmount(Node_t** head);


int findProfit(const Node_t* head_long_word, const Node_t* head_short_word);

int findShortWord(Node_t* head_long, Node_t* head_short, int* profit, int* cheker);

int findPlacesOfWordsAndProfit(Node_t* head_long, Node_t* head_short, int* place_long_word, int* place_short_word);

int chekerForProfit(int size_long_word, int size_short_word, int profit);



void makeStackOfWords(Node_t** head_long, Node_t** head_short, Word_c** list);


void compression(Word_c* list);

void addLibrary(Word_c* list, FILE* text_compr);

char* changeOneStr(char** str, Word_c* list);

void changePairOneString(char** str, Word_c* pair);

void changeWord(char** str, Word_c* pair, char* word, int* end_word);


char* makeSymbol();

char* makeString(const Word_c* list);

void addWordToString(char** str,const char* word, int* counter);

