#include"words.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TEN_KB 10240
#define NO_TRANSFER 0
#define TRANSFER '-'
#define STRING_SYMBOLS 3

#define ADD_PAIR 1
#define NO_PAIR 0

#define STRING_NULL 1
#define BRODE_STRING_FAIL 1

#define PROFIT 1
#define NO_PROFIT 0

#define LONGEST_SHORT_WORD 3


char* memoryForWord(const char*word_for_memory)
{
	char* word;
	word = (char*)calloc(strnlen_s(word_for_memory,TEN_KB) + 1, sizeof(char));
	return word;
}

void getStr(char** str, FILE* text)
{
    if (*str != NULL)
    {
        char* storer = (char*)realloc(*str, TEN_KB * sizeof(char));
        if (storer != NULL)
        {
            *str = storer;
        }
        fgets(*str, TEN_KB, text);
        storer = (char*)realloc(*str, (strnlen_s(*str,(size_t)TEN_KB) + 1) * sizeof(char));
        if (storer != NULL)
        {
            *str = storer;
        }
        else
        {
            exit(STRING_NULL);
        }
    }
}


char* wordCopy(const char* str, int index,int size)
{
    char* word = (char*)calloc(size + 1, sizeof(char));
    if (word != NULL)
    {
        for (int i = index, j = 0; j < size; i++, j++)
        {
            *(word + j) = *(str + i);
        }
    }
    return word;
}

int findSizeOfWOrd(const char* str, int *index)
{
    int size = 0;
    while ((*(str + *index) >= 'A' && *(str + *index) <= 'Z') || (*(str + *index) >= 'a' && *(str + *index) <= 'z') || (*(str + *index) >= '�' && *(str + *index) <= '�') || (*(str + *index) >= '�' && *(str + *index) <= '�'))
    {
        size++;
        (* index)++;
    }


    return size;
}

void takeWordsFromString(FILE* text, Node_t** head)
{
    char* str = (char*)calloc(TEN_KB, sizeof(char));
    getStr(&str, text);

    int i = 0;
    while(*(str+i)!='\0')
    {      
        if ((*(str + i) >= 'A' && *(str + i) <= 'Z') || (*(str + i) >= 'a' && *(str + i) <= 'z') || (*(str + i) >= '�' && *(str + i) <= '�') || (*(str + i) >= '�' && *(str + i) <= '�'))
        {           
            int size = findSizeOfWOrd(str, &i);
            char* word = wordCopy(str, i-size,size);          
            
            addWordInStack(head, word);
        }
        i++;
    }

    free(str);
}



void findWordsAmount(Node_t** head)
{
    FILE* text;
    errno_t err = fopen_s(&text, "D:\\Labi\\Nedorosl.txt", "r");
    if (err != 0)
    {
        printf("Cant open file");
    }
    else
    {
        while (!feof(text))
        {           
           takeWordsFromString(text,head);
        }
        fclose(text);
    }
    
}

int findProfit(const Node_t* head_long_word,const Node_t* head_short_word)
{
    int profit = (head_long_word->size * (head_long_word->amount) + head_short_word->size * (head_short_word->amount)) - (head_long_word->size * (head_short_word->amount) + head_short_word->size * (head_long_word->amount));

    return profit;
}



int findShortWord(const Node_t* head_long, Node_t* head_short, int* profit, int* cheker)
{
    int place = 1;
    int place_of_word = 0;

    while (head_short)
    {
        if (head_short->using == NO_USED)
        {            
            if (*cheker == 0)
            {
                *profit = findProfit(head_long,head_short);
                *cheker = 1;
                place_of_word = place;
            }

            if (findProfit(head_long, head_short) > *profit)
            {
                place_of_word = place;
                *profit = findProfit(head_long, head_short);
            }
        }
        place++;

        head_short = head_short->next;
    }

    return place_of_word;
}

int findPlacesOfWordsAndProfit(Node_t* head_long, Node_t* head_short, int* place_long_word, int* place_short_word)
{
    int place = 1;
    int profit = 0;
    int cheker = 0;

    while (head_long)
    {
        if (head_long->using == NO_USED)
        {
            int profit_before = profit;
            int tmp_place = findShortWord(head_long, head_short, &profit, &cheker);
            if (profit > profit_before)
            {
                *place_long_word = place;
                *place_short_word = tmp_place;
            }
            else
            {
                profit = profit_before;
            }

        }
        place++;
        head_long = head_long->next;
    }

    return profit;
}

int chekerForProfit(int size_long_word, int size_short_word, int profit)
{
    if (profit > size_long_word + size_short_word + STRING_SYMBOLS)
    {
        return PROFIT;
    }
    return NO_PROFIT;
}

void makeStackOfWords(Node_t** head_long, Node_t** head_short, Word_c ** list)
{


    int flg = ADD_PAIR;    
    do
    {
        int place_long_word = 0;
        int place_short_word = 0;

        int profit= findPlacesOfWordsAndProfit(*head_long,*head_short, &place_long_word, &place_short_word);
              
        char* long_word = takeWordFromStack(*head_long, place_long_word);     
        char* short_word = takeWordFromStack(*head_short, place_short_word);
                
        if (chekerForProfit((int)strnlen_s(long_word,TEN_KB), (int)strnlen_s(short_word,TEN_KB) ,profit) == PROFIT && flg == ADD_PAIR)
        {                                            
            pushWord(list, long_word, short_word);                      
        }
        else
        {
            flg = NO_PAIR;
        } 

    } while (flg);  
   
    freeStackAmount(head_long);
    freeStackAmount(head_long);
}

char* makeSymbol()
{
    char* symb = calloc(3, sizeof(char));
    if (symb)
    {
        *(symb + 0) = '&';
        *(symb + 1) = '\n';
    }
    return symb;
}

char* makeString(const Word_c* list)
{
    int size = (int)strnlen_s(list->word_long,TEN_KB) + (int)strnlen_s(list->word_short,TEN_KB) + 3;
    char* str = calloc(size, sizeof(char));
    return str;
}

void addWordToString(char**str,const char* word,int *counter)
{
    int i = 0;
    while (*(word + i) != '\0')
    {
        *(*str + *counter) = *(word + i);
        i++;
        (*counter)++;
    }    
}