#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 2147483647

struct stack_char {
	int count;
	char buffer[1000];
};

typedef struct stack_char Node;

char pop(Node* stack) {
	if (stack->count != 0) {
		--(stack->count);
		return stack->buffer[stack->count];
	}
	else {
		printf("syntax error");
		return 'a';
	}
}

char peek(const Node* stack) {
	if (stack->count != 0) {
		return stack->buffer[stack->count - 1];
	}
	else {
		return '\n';
	}
}

int push(Node* stack, char elem) {
	if (stack->count > 999) {
		return 0;
	}
	else {
		stack->buffer[stack->count] = elem;
		++(stack->count);
		return 1;
	}
}

struct stack_int {
	int count;
	int buffer[1000];
};

typedef struct stack_int Node_int;

int pop_int(Node_int* stack) {
	if (stack->count != 0) {
		--(stack->count);
		return stack->buffer[stack->count];
	}
	else {
		printf("syntax error");
		return MAX;
	}
}

int push_int(Node_int* stack, int elem) {
	if (stack->count > 999) {
		return 0;
	}
	else {
		stack->buffer[stack->count] = elem;
		++(stack->count);
		return 1;
	}
}

int check_number(char elem) {
	if (elem >= '0' && elem <= '9') {
		return 1;
	}
	else {
		return 0;
	}
}

int check_exit(char* str) {
	int i = 0;
	while (str[i] != '\0') {
		i++;
	}
	if (i == 4) {
		if (str[0] == 'e' && str[1] == 'x' && str[2] == 'i' && str[3] == 't') {
			return 0;
		}
	}
	return 1;
}

int post_notation(char* str, char* new_str) {
	int j = 0;
	int i = 0;
	int check = 0;
	Node stack_char;
	stack_char.count = 0;
	for (i = 0;;) {
		if (check == 0) {
			if (check_number(str[i])) {
				for (; check_number(str[i]); ++i, ++j) {
					new_str[j] = str[i];
				}
				new_str[j++] = ' ';
				check = 1;
			}
			else if (str[i] == '(') {
				push(&stack_char, '(');
				++i;
			}
			else {
				printf("syntax error");
				return -1;
			}
		}
		else {
			switch (str[i])
			{
			case '+':
			case '-':
				for (; peek(&stack_char) != '(' && peek(&stack_char) != '\n';) {
					new_str[j++] = pop(&stack_char);
					int k = j;
					if (new_str[k - 1] == 'a') {
						return -1;
					}
					new_str[j++] = ' ';
				}
				push(&stack_char, str[i]);
				check = 0;
				break;
			case '/':
			case '*':
				for (; peek(&stack_char) == '/' || peek(&stack_char) == '*';) {
					new_str[j++] = pop(&stack_char);
					int k = j;
					if (new_str[k - 1] == 'a') {
						return -1;
					}
					new_str[j++] = ' ';
				}
				push(&stack_char, str[i]);
				check = 0;
				break;
			case ')':
				for (; peek(&stack_char) != '(';) {
					new_str[j++] = pop(&stack_char);
					int k = j;
					if (new_str[k - 1] == 'a') {
						return -1;
					}
					new_str[j++] = ' ';
				}
				if (pop(&stack_char) == 'a') {
					return -1;
				}
				break;
			case '\n':
				for (; peek(&stack_char) != '\n';) {
					if (peek(&stack_char) == '(') {
						printf("syntax error");
						return -1;
					}
					new_str[j++] = pop(&stack_char);
					int k = j;
					if (new_str[k - 1] == 'a') {
						return -1;
					}
					new_str[j++] = ' ';
				}
				new_str[j] = '\n';
				return 0;
			default:
				printf("syntax error");
				return -1;
			}
			++i;
		}
	}
}

int calculating_value(char* new_string) {
	Node_int stack_int;
	stack_int.count = 0;
	for (int i = 0; new_string[i] != '\n'; ++i) {
		if (check_number(new_string[i])) {
			push_int(&stack_int, atoi(new_string + i));
			for (; new_string[i] != ' '; ++i);
		}
		else {
			int right_value = pop_int(&stack_int);
			if (right_value == MAX) {
				return MAX;
			}
			int left_value = pop_int(&stack_int);
			if (left_value == MAX) {
				return MAX;
			}
			switch (new_string[i]) {
			case '+':
				push_int(&stack_int, left_value + right_value);
				break;
			case '-':
				push_int(&stack_int, left_value - right_value);
				break;
			case '*':
				push_int(&stack_int, left_value * right_value);
				break;
			case '/':
				if (right_value == 0) {
					printf("division by zero");
					return 0;
				}
				push_int(&stack_int, left_value / right_value);
				break;
			}
			++i;
		}
	}
	return pop_int(&stack_int);

}

int main(int argc, char* argv[]) {
	char str[2000];
	char new_str[4000];
	int flag = 1;
	if (argc > 1) {
		if (argv[1][0] == '-' && argv[1][1] == 'i') {
			while (flag) {
				if (fgets(str, 2000, stdin) == NULL) {
					printf("syntax error");
					continue;
				}
				if (check_exit(str) == 0) {
					break;
				}
				if (post_notation(str, new_str) == -1) {
					continue;
				}
				int result = calculating_value(new_str);
				if (result == MAX) {
					printf("syntax error");
					continue;
				}
				printf("%d", result);
			}
		}
	}
	else {
		if (fgets(str, 2000, stdin) == NULL) {
			printf("syntax error");
			return 0;
		}
		if (post_notation(str, new_str) == -1) {
			return 0;
		}
		int result = calculating_value(new_str);
		if (result == MAX) {
			printf("syntax error");
			return 0;
		}
		printf("%d", result);
	}
	return 0;
}
