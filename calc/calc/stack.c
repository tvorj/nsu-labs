#include <malloc.h>
#include "laba.h"

Node* push (Node *top, char a) {
    Node *new_top = (Node *) malloc(sizeof(Node));
    new_top->next = top;
    new_top->elem = a;
    return new_top;
}

Node* pop (Node *top, char *a) {
    Node *new_top = top->next;
    free(top);
    return new_top;
}

bool isempty(Node *top) {
    return top == NULL;
}

void push_int (Node_int **top, int a) {
    Node_int *old_top = *top;
    *top = (Node_int *) malloc(sizeof(Node_int));
    (*top)->next = old_top;
    (*top)->number = a;
}

int pop_int (Node_int **top) {
    Node_int *new_top = (*top)->next;
    int value = (*top)->number;
    free(*top);
    *top = new_top;
    return value;
}

bool isempty_int(Node_int *top) {
    return top == NULL;
}