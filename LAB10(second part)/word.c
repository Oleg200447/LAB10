#include "Header.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TEN_KB 10240
#define SPEC_SYMBOL "&\n\0"

char* memoryForWord(char* word_for_memory)
{
    char* word;
    word = (char*)calloc(strlen(word_for_memory) + 1, sizeof(char));
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
        storer = (char*)realloc(*str, (strlen(*str) + 1) * sizeof(char));
        if (storer != NULL)
        {
            *str = storer;
        }
    }
}

char* wordCopy(char* str, int index, int size)
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

int findSizeOfWOrd(char* str, int* index)
{
    int size = 0;
    while ((*(str + *index) >= 'A' && *(str + *index) <= 'Z') || (*(str + *index) >= 'a' && *(str + *index) <= 'z') || (*(str + *index) >= 'À' && *(str + *index) <= 'ß') || (*(str + *index) >= 'à' && *(str + *index) <= 'ÿ'))
    {
        size++;
        (*index)++;
    }

    return size;
}

void findSpecSymbol(FILE* text)
{
    char* str = calloc(TEN_KB, sizeof(char));

    if (str!=NULL)
    {
        while (!feof(text) && strcmp(str, SPEC_SYMBOL) != 0)
        {
            fgets(str,TEN_KB, text);
        }
    }
    free(str);
}

void takeInfo(Word_c** head,FILE* text)
{
    char* str = calloc(TEN_KB, sizeof(char));

    fgets(str, TEN_KB, text);

    while (!feof(text) && strcmp(str, SPEC_SYMBOL) != 0)
    {
        int pos_in_str = 0;

        char* long_word = takeWordsFromString(str, &pos_in_str);
        char* short_word = takeWordsFromString(str, &pos_in_str);

        fgets(str, TEN_KB, text);

        pushWord(head, long_word, short_word);
    }

    free(str);
}

void makeStackOfWords(Word_c** head)
{
	FILE* text;
	errno_t err_file = fopen_s(&text, "D:\\Labi\\test3.txt", "r");

    if (err_file != 0)
    {
        printf("Cant open file");
    }
    else
    {
        findSpecSymbol(text);

        takeInfo(head, text);
      
        fclose(text);
    }

}

char* takeWordsFromString(char* str,int *pos_in_str)
{
    int i = *pos_in_str;
    char* word = NULL;;
    while (*(str + i) != '\0')
    {
        if ((*(str + i) >= 'A' && *(str + i) <= 'Z') || (*(str + i) >= 'a' && *(str + i) <= 'z') || (*(str + i) >= 'À' && *(str + i) <= 'ß') || (*(str + i) >= 'à' && *(str + i) <= 'ÿ'))
        {
            int size = findSizeOfWOrd(str, &i);
            word = wordCopy(str, i - size, size);
            break;
        }
        i++;
    }
    *pos_in_str = i;

    return word;
}