#include"compression.h"
#include"words.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<io.h>

#define TEN_KB 10240
#define NULL_ENTER_SYMBOL 1

#define TEN_KB 10240

void changeWord(char** str,const Word_c* pair,const char* word, int *end_word)
{
    if (strcmp(word,pair->word_short)==0)
    {
        int start_word = *end_word - (int)strnlen_s(word, TEN_KB);
        int def_in_size = (int)strnlen_s(pair->word_long, TEN_KB) - (int)strnlen_s(pair->word_short,TEN_KB);
        int size_new_str = ((int)strnlen_s(*str, TEN_KB) + def_in_size + NULL_ENTER_SYMBOL);

        char* storer = (char*)realloc(*str, size_new_str * sizeof(char));
        if (storer != NULL)
        {
            *str = storer;
        }

        if (storer == NULL)
        {
            free(*str);
            free(pair->word_long);
            free(pair->word_short);
            free(word);

            exit(NULL_ENTER_SYMBOL);
        }

        for (int i = size_new_str; i > start_word+ def_in_size; i--)
        {
            *(*str + i) = *(*str + i - def_in_size);
        }

        for (int i = start_word, j = 0; i < start_word + (int)strnlen_s(pair->word_long, TEN_KB); i++, j++)
        {
            *(*str + i) = *(pair->word_long + j);
            *end_word = i + 1;
        }         
    }

    if (strcmp(word ,pair->word_long)==0)
    {
        if (*str != NULL && pair->word_short != NULL)
        {
            int start_word = *end_word - (int)strnlen_s(word, TEN_KB);
            int def_in_size = (int)strnlen_s(pair->word_long, TEN_KB) - (int)strnlen_s(pair->word_short, TEN_KB);
            int size_old_str = (int)strnlen_s(*str, TEN_KB);
            int size_new_str = ((int)strnlen_s(*str, TEN_KB) - def_in_size + NULL_ENTER_SYMBOL);

            for (int i = start_word + 1; i < size_old_str - def_in_size + 1; i++)
            {
                *(*str + i) = *(*str + i + def_in_size);
            }

            for (int i = start_word, j = 0; i < start_word + (int)strnlen_s(pair->word_short, TEN_KB); i++, j++)
            {
                *(*str + i) = *(pair->word_short + j);
                *end_word = i + 1;
            }

            char* storer = (char*)realloc(*str, size_new_str * sizeof(char));
            if (storer != NULL)
            {
                *str = storer;
            }
        }
    }
}

void changePairOneString(char** str,const Word_c* pair)
{   
    int place_in_str = 0;

    while(place_in_str+1< (int)strnlen_s(*str, TEN_KB))
    {
        if ((*(*str + place_in_str) >= 'A' && *(*str + place_in_str) <= 'Z') || (*(*str + place_in_str) >= 'a' && *(*str + place_in_str) <= 'z') || (*(*str + place_in_str) >= 'À' && *(*str + place_in_str) <= 'ß') || (*(*str + place_in_str) >= 'à' && *(*str + place_in_str) <= 'ÿ'))
        {
            int size = findSizeOfWOrd(*str, &place_in_str);
            const char* word = wordCopy(*str, place_in_str - size, size);

            changeWord(str, pair, word, &place_in_str);
        }
        else
        {
            place_in_str++;
        }

    }

}


char*  changeOneStr(char ** str, Word_c* list)
{
     while (list)
     {           
        changePairOneString(str, list);

        list = list->next;
     }
            
    return *str;
}

void addLibrary(Word_c* list,FILE*text_compr)
{
    const char* symb = makeSymbol();
    
    fputs(symb, text_compr);

    while (list)
    {
        char* str = makeString(list);

        if (str != NULL)
        {
            int counter = 0;
            addWordToString(&str, list->word_long, &counter);
            *(str + counter) = ' ';
            counter++;
            addWordToString(&str, list->word_short, &counter);
            *(str + counter) = '\n';
            counter++;       

            fputs(str, text_compr);           
        }

        list = list->next;
    }

    fputs(symb, text_compr);
}

void compression(Word_c* list)
{
    FILE* text_compr;
    errno_t err_file_compr = fopen_s(&text_compr, "D:\\Labi\\test3.txt", "w+");

    FILE* text;
    errno_t err_file = fopen_s(&text, "D:\\Labi\\Nedorosl.txt", "r+");

    if (err_file_compr != 0 || err_file!=0)
    {
        printf("Cant open file");
    }
    else
    {
        addLibrary(list, text_compr);

        char* str_before = (char*)calloc(TEN_KB, sizeof(char));
        if (str_before == NULL)
        {
            freeStackWord(list);
            exit(NULL_ENTER_SYMBOL);
        }

        while (!feof(text))
        {           
            getStr(&str_before, text);
            changeOneStr(&str_before, list);
            if (feof(text))
            {
                break;
            }
            fputs(str_before, text_compr);                   
        }       
   
        fclose(text_compr);
        fclose(text);

        free(str_before);
        freeStackWord(&list);
    }
}




