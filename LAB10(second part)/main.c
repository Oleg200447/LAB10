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

	FILE* text_compr;
	errno_t err_file_compr = fopen_s(&text_compr, "D:\\Labi\\test2.txt", "r+");

	FILE* text;
	errno_t err_file = fopen_s(&text, "D:\\Labi\\Nedorosl.txt", "r+");
	if (err_file_compr != 0 || err_file != 0)
	{
		printf("Cant open file");
	}
	else
	{
		char* str1 = calloc(10000, sizeof(char));
		char* str2 = calloc(10000, sizeof(char));
		while (!feof(text))
		{
			getStr(&str1, text);
			getStr(&str2, text_compr);
			if (strcmp(str1, str2) != 0)
			{
				printf("%s\n", str1);
				printf("%s\n\n\n\n", str2);

			}
		}

		fclose(text);
		fclose(text_compr);
	}
	return 0;
}