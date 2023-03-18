#include"stack.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FIRST_TIME_MEET 1
#define EQUAL 0

#define LONGEST_SHORT_WORD 3


void pushAmount(Node_t** head, char* word,int amount) {
    Node_t* storer = malloc(sizeof(Node_t));
    if (storer == NULL) {
        exit(EXIT_FAILURE);
    }
    storer->next = *head;
    storer->amount = amount;
    storer->word=memoryForWord(word);
    storer->word = word;
    storer->size =(int) strlen(word);
    storer->using = NO_USED;
    *head = storer;
}

Node_t* popAmount(Node_t** head) {
    Node_t* out;
    if ((*head) == NULL) {
        exit(EXIT_FAILURE);
    }
    out = *head;
    *head = (*head)->next;
    return out;
}


void showStackAmount(const Node_t* head) {   
    while (head) {
        printf("%s ", head->word);
        printf("%d ", head->amount);
        head = head->next;
    }
}

void freeStackAmount(Node_t** head)
{
    while (*head)
    {
        Node_t* tmp = *head;
        if ((*head)->using == NO_USED)
        {
            free((*head)->word);
        }
        *head = (*head)->next;
        free(tmp);
    }
}


void pushWord(Word_c** head, char* word_long,char* word_short) {
    Word_c* storer = malloc(sizeof(Word_c));
    if (storer == NULL) {
        exit(EXIT_FAILURE);
    }
    storer->next = *head;
    storer->word_long = memoryForWord(word_long);
    storer->word_long=word_long;
    storer->word_short = memoryForWord(word_short);
    storer->word_short = word_short;
    *head = storer;
}

Word_c* popWord(Word_c** head) {
   Word_c* out;
    if ((*head) == NULL) {
        exit(EXIT_FAILURE);
    }
    out = *head;
    *head = (*head)->next;
    return out;
}

void showStackWord(const Word_c* head) {
    while (head) {
        printf("%s ", head->word_long);
        printf("%s\n", head->word_short);
        head = head->next;
    }
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



Node_t* chekerForWordInStack(Node_t* head,const char* word)
{
    Node_t* tmp = head;
    while (tmp)
    {
        if (strcmp(tmp->word, word) == EQUAL)
        {
            return tmp;
        }
        tmp = tmp->next;
    }

    return tmp;
}

void addWordInStack(Node_t** head,char * word)
{
   
    Node_t* storer = chekerForWordInStack(*head, word);

    if (storer != NULL)
    {
        (storer->amount)++;
    }
    else
    {
        pushAmount(head, word, FIRST_TIME_MEET);
    }
}

char* takeWordFromStack(Node_t* head,int place)
{
    for (int i = 1; i < place; i++)
    {
        head = head->next;
    }

    head->using = USED;  

    return head->word;
}




void makeTwoStacks(Node_t** head, Node_t** head_long_words, Node_t** head_short_words)
{
    while (*head)
    {
        Node_t* storer = popAmount(head);
        if (storer->size > LONGEST_SHORT_WORD)
        {
            pushAmount(head_long_words, storer->word, storer->amount);
        }
        else
        {
            pushAmount(head_short_words, storer->word, storer->amount);
        }
    }
}