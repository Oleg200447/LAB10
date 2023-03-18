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

Node_t* chekerForWordInStack(Node_t* head,const char* word);

void addWordInStack(Node_t** head, char* word);

void freeStackAmount(Node_t** head);

char* takeWordFromStack(Node_t* head, int place);



Word_c* popWord(Word_c** head);

void pushWord(Word_c** head, char* word_long, char* word_short);

void showStackWord(const Word_c* head);

void freeStackWord(Word_c** head);


void makeTwoStacks(Node_t** head, Node_t** head_long_words, Node_t** head_short_words);


void makeStackOfWords(Node_t** head_long, Node_t** head_short, Word_c** list);



