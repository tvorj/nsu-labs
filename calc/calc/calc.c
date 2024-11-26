#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#include "laba.h"

int binpow(int x, int p)
{
	if(p == 0) return 1;
	if(p == 1) return x;
	int u = binpow(x, p / 2);
	u *= u;
	if(p % 2 == 1)
	{
		u = u * x;
	}

	return u;
}


void calculating_value()
{
	FILE* file = fopen("postfix_notation.txt", "r");
	FILE* file_ans = fopen("rez.dat", "w");
	struct Node_int *root = NULL;
	char* str = (char*)calloc(100, sizeof(char));
	while(fgets(str, 100, file) != NULL)
	{
		int i = 0;
		for(i = 0; i < strlen(str) - 1; i++)
		{
			if(isdigit(str[i]))
			{	
				int c = (int)(str[i] - '0');
				push_int(&root, c);
			}
			else
			{
				int val2 = pop_int(&root);
				if(isempty_int(root))
				{
					push_int(&root, -val2);
					continue;
				}
				int val1 = pop_int(&root);
				int ans = 0;
				if(str[i] == '+')
				{
					ans = val1 + val2;
				}
				else if(str[i] == '-')
				{
					ans = val1 - val2;
				}
				else if(str[i] == '^')
				{
					ans = binpow(val1, val2);
				}
				else if(str[i] == '*')
				{
					ans = val1 * val2;
				}
				else
				{
					ans = val1 / val2;
				}
				push_int(&root, ans);

			}

		}
		int ans = pop_int(&root);
		fprintf(file_ans, "%d\n", ans);
	}

	free(str);
	fclose(file);
	fclose(file_ans);
}