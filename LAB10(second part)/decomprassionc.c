#include"Header.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<io.h>

#define TEN_KB 10240
#define NULL_ENTER_SYMBOL 1
#define SPEC_SYMBOL "&\n\0"

void changeWord(char** str, Word_c* pair, char* word, int* end_word)
{
    if (strcmp(word, pair->word_short) == 0)
    {
        int start_word = *end_word - (int)strlen(word);
        int def_in_size = (int)strlen(pair->word_long) - (int)strlen(pair->word_short);
        int size_new_str = ((int)strlen(*str) + def_in_size + NULL_ENTER_SYMBOL);

        char* storer = (char*)realloc(*str, size_new_str * sizeof(char));
        if (storer != NULL)
        {
            *str = storer;
        }

        for (int i = size_new_str; i > start_word + def_in_size; i--)
        {
            *(*str + i) = *(*str + i - def_in_size);
        }

        for (int i = start_word, j = 0; i < start_word + strlen(pair->word_long); i++, j++)
        {
            *(*str + i) = *(pair->word_long + j);
            (* end_word) = i + 1;
        }
    }

    if (strcmp(word, pair->word_long) == 0)
    {
        int start_word = *end_word - (int)strlen(word);
        int def_in_size = (int)strlen(pair->word_long) - (int)strlen(pair->word_short);
        int size_old_str = (int)strlen(*str);
        int size_new_str = ((int)strlen(*str) - def_in_size + NULL_ENTER_SYMBOL);

        for (int i = start_word + 1; i < size_old_str - def_in_size + 1; i++)
        {
            *(*str + i) = *(*str + i + def_in_size);
        }

        for (int i = start_word, j = 0; i < start_word + strlen(pair->word_short); i++, j++)
        {
            *(*str + i) = *(pair->word_short + j);
            (* end_word) = i + 1;
        }

        char* storer = (char*)realloc(*str, size_new_str * sizeof(char));
        if (storer != NULL)
        {
            *str = storer;
        }
    }
}

void changePairOneString(char** str, Word_c* pair)
{
    int pos_for_next = 0;
    int place_in_str = 0;

    while (place_in_str + 1 < (int)strlen(*str))
    {
        if ((*(*str + place_in_str) >= 'A' && *(*str + place_in_str) <= 'Z') || (*(*str + place_in_str) >= 'a' && *(*str + place_in_str) <= 'z') || (*(*str + place_in_str) >= '�' && *(*str + place_in_str) <= '�') || (*(*str + place_in_str) >= '�' && *(*str + place_in_str) <= '�'))
        {
            int size = findSizeOfWOrd(*str, &place_in_str);
            char* word = wordCopy(*str, place_in_str - size, size);

            changeWord(str, pair, word, &place_in_str);
        }
        else
        {
            place_in_str++;
        }

    }

}


char* changeOneStr(char** str, Word_c* list)
{
    while (list)
    {
        changePairOneString(str, list);

        list = list->next;
    }

    return *str;
}

void goToInfo(FILE* text)
{
    char* str = (char*)calloc(TEN_KB, sizeof(char));
    if (str != NULL)
    {
        findSpecSymbol(text);
        fgets(str, TEN_KB, text);
        findSpecSymbol(text);
    }

    free(str);
}

void decompression(Word_c* list)
{
    FILE* text_compr;
    errno_t err_file_compr = fopen_s(&text_compr, "D:\\Labi\\test2.txt", "w+");

    FILE* text;
    errno_t err_file = fopen_s(&text, "D:\\Labi\\test3.txt", "r+");

    if (err_file_compr != 0 || err_file != 0)
    {
        printf("Cant open file");
    }
    else
    {
        goToInfo(text);

        char* str_before = (char*)calloc(TEN_KB, sizeof(char));

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