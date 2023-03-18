#include <stdio.h>
#include"Header.h"
#include<stdlib.h>
#include<string.h>

int main()
{
	system("chcp 1251");
	system("cls");

	Node_t* head = NULL;

	findWordsAmount(&head);

	Node_t* head_long_words = NULL;
	Node_t* head_short_words = NULL;

	makeTwoStacks(&head, &head_long_words, &head_short_words);

	Word_c* list = NULL;

	makeStackOfWords(&head_long_words,&head_short_words, &list);
	
	compression(list);
	


	return 0;
}