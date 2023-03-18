#include<stdio.h>
#include"Header.h"
#include<stdlib.h>
#include<string.h>

int main()
{
	system("chcp 1251");
	system("cls");

	Word_c* head = NULL;

	makeStackOfWords(&head);	

	decompression(head);

	return 0;
}