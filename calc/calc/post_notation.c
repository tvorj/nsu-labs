#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>

#include "laba.h"

char *post_conversion (char* S) {

    char t = '\0';

    char* new_str = (char*)calloc(50, sizeof(char));
    int i, j = 0;
    struct Node *st = NULL;
    for(i = 0; S[i] != '\n'; i++) {
        if (isdigit(S[i])) {
            new_str[j] = S[i];
            j++;
        }
        else if (S[i] == ')') {
            while (st->elem != '(' ) {
                new_str[j] = st->elem;
                st = pop(st, &t);
                j++;
            }
            st = pop(st, &t);
        }
        else {
            if(S[i] == '+' || S[i] == '-') {
                while(st != NULL && st->elem != '(') {
                    new_str[j] = st->elem;
                    st = pop(st, &t);
                    j++;
                }
            }
            else if(S[i] == '*' || S[i] == '/') {
                while(st != NULL && st->elem != '(' && st->elem != '+' && st->elem != '-') {
                    new_str[j] = st->elem;
                    st = pop(st,&t);
                    j++;
                }
            }
            st = push(st, S[i]);
        }
    }
    while (st != NULL) {
        new_str[j] = st->elem;
        st = pop(st, &t);
        j++;
    }
    new_str[j] = '\n';
    return new_str;
}


void post_notation (int N) {
    FILE* file = fopen("constant_expressions.txt", "r");
    FILE* file_post = fopen("postfix_notation.txt", "w");

    char** array_of_strings = (char**)calloc(N, sizeof(char*));

    int i;
    for(i = 0; i < N; i++) {
        char *str = (char *) calloc(50, sizeof(char ));
        fgets(str, 50, file);
        char *find = strchr(str, '\n');
        *(array_of_strings+i) = (char *) calloc(find - str + 1, sizeof(char));
        int j;
        for(j = 0; j < find - str + 1; j++) {
            *(*(array_of_strings+i)+j) = str[j];
        }
        char *p = post_conversion(*(array_of_strings+i));
        free(*(array_of_strings+i));
        *(array_of_strings+i) = p;
        fputs(*(array_of_strings+i), file_post);
    }
    fclose(file);
    fclose(file_post);
}
