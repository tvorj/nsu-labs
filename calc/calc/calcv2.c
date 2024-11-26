//#define _CRT_SECURE_NO_WARNINGS
//#include <stdio.h>
//#include <malloc.h>
//#include <stdbool.h>
//#include <stdlib.h>
//#include <string.h>
//#include <stddef.h> 
//#include <ctype.h>
//
//
//typedef struct Node {
//    char elem;
//    struct Node* next;
//} Node;
//
//
//typedef struct Node_int {
//    int number;
//    struct Node_int* next;
//} Node_int;
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
//char* post_conversion(char* S) {
//    char t = '\0';
//    char* new_str = (char*)calloc(1000, sizeof(char));
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
//
//int main() {
//    int N = clipping_expressions();
//    post_notation(N);
//   	calculating_value();
//    return 0;
//}