//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <malloc.h>
//#include <stdbool.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stddef.h> 
//#include <ctype.h>
//
//typedef struct Node {
//	char elem;
//	struct Node* next;
//} Node;
//
//typedef struct Node_int {
//	int number;
//	struct Node_int* next;
//} Node_int;
//
////Node* push(Node* top, char a);
////Node* pop(Node* top, char* a);
////bool isempty(Node* top);
////
////void push_int(Node_int** top, int a);
////int pop_int(Node_int** top);
////bool isempty_int(Node_int* top);
////
////void calculating_value();
////char* post_conversion(char* S);
////void post_notation(int N);
////int clipping_expressions();
//
//
//Node* push(Node* top, char a) {
//    Node* new_top = (Node*)malloc(sizeof(Node));
//    new_top->next = top;
//    new_top->elem = a;
//    return new_top;
//}
//
//
//Node* pop(Node* top, char* a) {
//    Node* new_top = top->next;
//    free(top);
//    return new_top;
//}
//
//
//bool isempty(Node* top) {
//    return top == NULL;
//}
//
//
//void push_int(Node_int** top, int a) {
//    Node_int* old_top = *top;
//    *top = (Node_int*)malloc(sizeof(Node_int));
//    (*top)->next = old_top;
//    (*top)->number = a;
//}
//
//
//int pop_int(Node_int** top) {
//    Node_int* new_top = (*top)->next;
//    int value = (*top)->number;
//    free(*top);
//    *top = new_top;
//    return value;
//}
//
//
//bool isempty_int(Node_int* top) {
//    return top == NULL;
//}
//
//
//int clipping_expressions()
//{
//    FILE* file = fopen("program.txt", "r");
//    FILE* const_file = fopen("constant_expressions.txt", "w");
//
//    char* str = (char*)calloc(100, sizeof(char));
//    char* find = (char*)calloc(100, sizeof(char));
//    char c;
//    int k = 0;
//
//    while (fgets(str, 100, file) != NULL) {
//        //printf("str = %s\n", str);
//        if ((find = strchr(str, '=')) != NULL) {
//            while ((c = *++find) != ';')
//                fputc(c, const_file);
//            fputc('\n', const_file);
//            k++;
//        }
//    }
//
//
//    fclose(file);
//    fclose(const_file);
//
//    return k;
//}
//
//
//char* post_conversion(char* S) {
//
//    char t = '\0';
//
//    char* new_str = (char*)calloc(50, sizeof(char));
//    int i, j = 0;
//    struct Node* st = NULL;
//    for (i = 0; S[i] != '\n'; i++) {
//        if (isdigit(S[i])) {
//            new_str[j] = S[i];
//            j++;
//        }
//        else if (S[i] == ')') {
//            while (st->elem != '(') {
//                new_str[j] = st->elem;
//                st = pop(st, &t);
//                j++;
//            }
//            st = pop(st, &t);
//        }
//        else {
//            if (S[i] == '+' || S[i] == '-') {
//                while (st != NULL && st->elem != '(') {
//                    new_str[j] = st->elem;
//                    st = pop(st, &t);
//                    j++;
//                }
//            }
//            else if (S[i] == '*' || S[i] == '/') {
//                while (st != NULL && st->elem != '(' && st->elem != '+' && st->elem != '-') {
//                    new_str[j] = st->elem;
//                    st = pop(st, &t);
//                    j++;
//                }
//            }
//            st = push(st, S[i]);
//        }
//    }
//    while (st != NULL) {
//        new_str[j] = st->elem;
//        st = pop(st, &t);
//        j++;
//    }
//    new_str[j] = '\n';
//    return new_str;
//}
//
//
//void post_notation(int N) {
//    FILE* file = fopen("constant_expressions.txt", "r");
//    FILE* file_post = fopen("postfix_notation.txt", "w");
//
//    char** array_of_strings = (char**)calloc(N, sizeof(char*));
//
//    int i;
//    for (i = 0; i < N; i++) {
//        char* str = (char*)calloc(50, sizeof(char));
//        fgets(str, 50, file);
//        char* find = strchr(str, '\n');
//        *(array_of_strings + i) = (char*)calloc(find - str + 1, sizeof(char));
//        int j;
//        for (j = 0; j < find - str + 1; j++) {
//            *(*(array_of_strings + i) + j) = str[j];
//        }
//        char* p = post_conversion(*(array_of_strings + i));
//        free(*(array_of_strings + i));
//        *(array_of_strings + i) = p;
//        fputs(*(array_of_strings + i), file_post);
//    }
//    fclose(file);
//    fclose(file_post);
//}
//
//
//int binpow(int x, int p)
//{
//    if (p == 0) return 1;
//    if (p == 1) return x;
//    int u = binpow(x, p / 2);
//    u *= u;
//    if (p % 2 == 1)
//    {
//        u = u * x;
//    }
//
//    return u;
//}
//
//
//void calculating_value()
//{
//    FILE* file = fopen("postfix_notation.txt", "r");
//    FILE* file_ans = fopen("rez.dat", "w");
//    struct Node_int* root = NULL;
//    char* str = (char*)calloc(100, sizeof(char));
//    while (fgets(str, 100, file) != NULL)
//    {
//        unsigned int i = 0;
//        for (i = 0; i < strlen(str) - 1; i++)
//        {
//            if (isdigit(str[i]))
//            {
//                int c = (int)(str[i] - '0');
//                push_int(&root, c);
//            }
//            else
//            {
//                int val2 = pop_int(&root);
//                if (isempty_int(root))
//                {
//                    push_int(&root, -val2);
//                    continue;
//                }
//                int val1 = pop_int(&root);
//                int ans = 0;
//                if (str[i] == '+')
//                {
//                    ans = val1 + val2;
//                }
//                else if (str[i] == '-')
//                {
//                    ans = val1 - val2;
//                }
//                else if (str[i] == '^')
//                {
//                    ans = binpow(val1, val2);
//                }
//                else if (str[i] == '*')
//                {
//                    ans = val1 * val2;
//                }
//                else
//                {
//                    ans = val1 / val2;
//                }
//                push_int(&root, ans);
//
//            }
//
//        }
//        int ans = pop_int(&root);
//        fprintf(file_ans, "%d\n", ans);
//    }
//
//    free(str);
//    fclose(file);
//    fclose(file_ans);
//}
//
//
//int main(){
//	int N = clipping_expressions();
//	post_notation(N);
//	calculating_value();
//	return 0;
//}
#include <stdio.h>
int main() {
	int k = 0;
	if (!k) {
		printf("1");
	}
	else {
		printf("2");
	}
	return 0;
}