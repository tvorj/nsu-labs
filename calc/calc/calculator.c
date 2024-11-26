//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//void fuc(char a[], int* n)
//{
//	char b, c[1000];
//	int k = -1;
//	while ((b = getc(stdin)) != ')')
//	{
//		if (b >= '0' && b <= '9')
//		{
//			(*n)++;
//			a[*n] = b;
//		}
//		else
//		{
//			if (b == '(')
//			{
//				fuc(a, n);
//				continue;
//			}
//			if (k == 1)
//			{
//				if (c[1] == '*' || c[1] == '/')
//				{
//					(*n)++;
//					a[*n] = c[1];
//				}
//				else
//				{
//					(*n)++;
//					a[*n] = c[0];
//					c[0] = c[1];
//				}
//				k--;
//			}
//			k++;
//			c[k] = b;
//		}
//	}
//	while (k >= 0)
//	{
//		(*n)++;
//		a[*n] = c[k];
//		k--;
//	}
//}
//int main()
//{
//	int* n = (int*)malloc(sizeof(int)), k = -1;
//	(*n) = -1;
//	char a[1000], b, c[1000];
//	while ((b = getc(stdin)) != '\n')
//	{
//		if (b >= '0' && b <= '9')
//		{
//			(*n)++;
//			a[*n] = b;
//		}
//		else
//		{
//			if (b == '(')
//			{
//				fuc(a, n);
//				continue;
//			}
//			if (k == 1)
//			{
//				if (c[1] == '*' || c[1] == '/')
//				{
//					(*n)++;
//					a[*n] = c[1];
//				}
//				else
//				{
//					(*n)++;
//					a[*n] = c[0];
//					c[0] = c[1];
//				}
//				k--;
//			}
//			k++;
//			c[k] = b;
//		}
//	}
//	while (k >= 0)
//	{
//		(*n)++;
//		a[*n] = c[k];
//		k--;
//	}
//	for (int i = 0; i <= (*n); i++)
//	{
//		printf("%c", a[i]);
//	}
//	return 0;
//}