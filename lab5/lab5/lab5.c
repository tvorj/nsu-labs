#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>

														//structures

typedef struct tree {
	struct tree* left;
	struct tree* right;
	char symbol;
	int usage;
} tree;


typedef struct text {
	struct text* next;
	tree* root;
} text;


void free_tree(tree* root) {
	if (root != NULL) {
		free_tree(root->right);
		free_tree(root->left);
		free(root);
	}
}


int max_in_array(int array[], int n, int* max_char) {
	int i, max = 0;
	*max_char = 0;
	for (i = 0; i < n; i++) {
		if (array[i] > max) {
			max = array[i];
			*max_char = i;
		}
	}
	array[*max_char] = 0;
	return max;
}


text* push(text* head, int num, char letter) {
	text* txt = (text*)malloc(sizeof(text));
	tree* tr = (tree*)malloc(sizeof(tree));
	assert(txt != NULL);
	assert(tr != NULL);
	tr->left = NULL;
	tr->right = NULL;
	tr->symbol = letter;
	tr->usage = num;
	txt->root = tr;
	txt->next = head;
	return txt;
}


int check_text(text* text) {
	int k;
	if (text->next == NULL) {
		k = 0;
	}
	else {
		k = 1;
	}
	return k;
}


void right_sub(text* text) {
	if (text->next != NULL) {
		if (text->next->root->usage < text->root->usage) {
			tree* temp = NULL;
			temp = text->next->root;
			text->next->root = text->root;
			text->root = temp;
			right_sub(text->next);
		}
	}
}


tree* tree_create(text* text2) {
	while (check_text(text2) == 1) {
		tree* tmp = (tree*)malloc(sizeof(tree));
		text* text1 = (text*)malloc(sizeof(text));
		assert(tmp != NULL);
		assert(text1 != NULL);
		if ((text2)->root->usage >= ((text2)->next)->root->usage) {
			tmp->left = (text2)->root;
			tmp->right = (text2)->next->root;
		}
		else {
			tmp->left = (text2)->next->root;
			tmp->right = text2->root;
		}
		tmp->usage = text2->root->usage + text2->next->root->usage;
		tmp->symbol = 0;
		text1->next = text2->next->next;
		text1->root = tmp;
		free(text2->next);
		free(text2);
		text2 = text1;
		right_sub(text2);
	}
	tree* ptr = text2->root;
	free(text2);
	return (ptr);
}


int is_symbol(tree* root, char sym, int* counter, int array[]) {
	int l = 1, r = 1;
	if (root->left != NULL) {
		l = is_symbol(root->left, sym, counter, array);
		if (l == 0) {
			array[*counter] = 0;
			*counter = *counter + 1;
		}
	}
	if (root->right != NULL) {
		r = is_symbol(root->right, sym, counter, array);
		if (r == 0) {
			array[*counter] = 1;
			*counter = *counter + 1;
		}
	}
	if ((root->left == NULL) && (root->right == NULL)) {
		if (root->symbol == sym) {
			l = 0;
			r = 0;
		}
		else {
			l = 1;
			r = 1;
		}
	}
	if ((l == 0) || (r == 0)) {
		return 0;
	}
	else {
		return 1;
	}
}

														//encode functions

void keyencode(tree* root, FILE* out, unsigned char* ch, int* counter) {
	if (*counter > 7) {
		fprintf(out, "%c", *ch);
		*ch = 0;
		*counter = 0;
	}
	if ((root->left != NULL) || (root->right != NULL)) {
		*ch = *ch << 1;
		*ch = *ch + 1;
		*counter = *counter + 1;
		keyencode(root->left, out, ch, counter);
		keyencode(root->right, out, ch, counter);
	}
	else {
		*ch = *ch << 1;
		*counter = *counter + 1;
		int i;
		for (i = 7; i >= 0; i--) {
			int byte = (root->symbol >> i) & 1;
			if (*counter > 7) {
				fprintf(out, "%c", *ch);
				*ch = 0;
				*counter = 0;
			}
			*ch = *ch << 1;
			*ch = *ch + byte;
			*counter = *counter + 1;
		}
	}
}


void textencode(FILE* in, FILE* out, tree* root) {
	fwrite(&root->usage, sizeof(int), 1, out);
	char c;
	unsigned char sym = 0;
	int buf_sym = 0;
	for (int i = 0; i < root->usage; i++) {
		c = fgetc(in);
		int array[256] = {0};
		int counter = 0;
		is_symbol(root, c, &counter, array);
		for (int i = counter - 1; i >= 0; i--) {
			sym = sym + (array[i]);
			buf_sym++;
			if (buf_sym > 7) {
				fprintf(out, "%c", sym);
				sym = sym << 8;
				buf_sym = 0;
			}
			else sym = sym << 1;
		}
	}
	if (buf_sym > 0) {
		sym = sym << (7 - buf_sym);
		fprintf(out, "%c", sym);
	}
}

														//decode functions

void keydecode(FILE* in, tree* root, unsigned char* ch, int* counter) {
	if (*counter < 0) {
		*ch = fgetc(in);
		*counter = 7;
	}
	if (((*ch >> *counter) & 1) == 0) {
		*counter = *counter - 1;
		int i;
		unsigned char sym = 0;
		for (i = 0; i < 8; i++) {
			if (*counter < 0) {
				*ch = fgetc(in);
				*counter = 7;
			}
			int byte = ((*ch >> *counter) & 1);
			sym = sym << 1;
			sym = sym + byte;
			*counter = *counter - 1;
		}
		root->symbol = sym;
		root->left = NULL;
		root->right = NULL;
	}
	else {
		*counter = *counter - 1;
		tree* trl = (tree*)malloc(sizeof(tree));
		tree* trr = (tree*)malloc(sizeof(tree));
		assert(trl != NULL);
		assert(trr != NULL);
		root->left = trl;
		root->right = trr;
		keydecode(in, root->left, ch, counter);
		keydecode(in, root->right, ch, counter);
	}
}


void textdecode(tree* root, FILE* out, FILE* in) {
	int len;
	/*fread(&len, sizeof(int), 1, in);*/
	size_t temp = fread(&len, sizeof(int), 1, in); // verno li srabotal fread
	if (temp == 0) {
		return;
	}
	/*fread(&len, sizeof(int), 1, in);*/
	unsigned char c = fgetc(in);
	int counter = 7;
	/*if (len == 18882592) {
		len = 4;
	}*/
	for (int i = 0; i < len; i++) {
		tree* tmp = root;
		while ((tmp->left != NULL) && (tmp->right != NULL)) {
			if (counter < 0) {
				counter = 7;
				c = fgetc(in);
			}
			int byte = (c >> counter) & 1;
			counter--;
			if (byte == 0) {
				tmp = tmp->left;
			}
			if (byte == 1) {
				tmp = tmp->right;
			}
		}
		fprintf(out, "%c", tmp->symbol);
	}
}

														//encode tester

void encode(FILE* in, FILE* out) {
	int c;
	c = fgetc(in);
	int table[256] = {0};
	text* text = NULL;
	if (c != EOF) {
		fseek(in, 0L, SEEK_SET);
		c = fgetc(in);
		while ((c = fgetc(in)) != EOF) {
			table[c]++;
		}
		int max;
		int max_char = 0;
		max = max_in_array(table, 256, &max_char);
		while (max > 0) {
			char tsymb = max_char;
			text = push(text, max, tsymb);
			max = max_in_array(table, 256, &max_char);
		}
		tree* Tree = tree_create(text);
		unsigned char symb = 0;
		int counter = 0;
		keyencode(Tree, out, &symb, &counter);
		symb = (symb << (8 - counter));
		fprintf(out, "%c", symb);
		fseek(in, 0L, SEEK_SET);
		c = fgetc(in);
		textencode(in, out, Tree);
		free_tree(Tree);
	}
}

														//encode interactive

void encode_int(FILE* in, FILE* out) {
	int c;
	c = fgetc(in);
	int table[256] = { 0 };
	text* text = NULL;
	if (c != EOF) {
		fseek(in, 0L, SEEK_SET);
		while ((c = fgetc(in)) != EOF) {
			table[c]++;
		}
		int max;
		int max_char = 0;
		max = max_in_array(table, 256, &max_char);
		while (max > 0) {
			char tsymb = max_char;
			text = push(text, max, tsymb);
			max = max_in_array(table, 256, &max_char);
		}
		tree* Tree = tree_create(text);
		unsigned char symb = 0;
		int counter = 0;
		keyencode(Tree, out, &symb, &counter);
		symb = (symb << (8 - counter));
		fprintf(out, "%c", symb);
		fseek(in, 0L, SEEK_SET);
		textencode(in, out, Tree);
		free_tree(Tree);
	}
}

														//decode tester

void decode(FILE* in, FILE* out) {
	tree* root = (tree*)malloc(sizeof(tree));
	assert(root != NULL);
	int c = fgetc(in);
	if (c == EOF) { 
		free(root);
		return;
	}
	if (c != EOF) {
		fseek(in, 0L, SEEK_SET);
		c = fgetc(in);
		int counter = 7;
		unsigned char ch = fgetc(in);
		keydecode(in, root, &ch, &counter);
		textdecode(root, out, in);
	}
	free_tree(root);
}

														//decode interactive

void decode_int(FILE* in, FILE* out) {
	tree* root = (tree*)malloc(sizeof(tree));
	assert(root != NULL);
	int c = fgetc(in);
	if (c != EOF) {
		fseek(in, 0L, SEEK_SET);
		int counter = 7;
		unsigned char ch = fgetc(in);
		keydecode(in, root, &ch, &counter);
		textdecode(root, out, in);
	}
	free_tree(root);
}


int main() {
														//interactive						
	/*if (strcmp(argv[1], "-c") == 0) {
		FILE* in = fopen(argv[2], "rb");
		FILE* out = fopen(argv[3], "wb");
		if (in == NULL) {
			fprintf(out, "Cant open file in.txt \n");
		}
		else {
			encode_int(in, out);
		}
		if (in == 0) {
			fclose(out);
			return 0;
		}
		fclose(in);
		fclose(out);
		return 0;
	}
	if (strcmp(argv[1], "-d") == 0) {
		FILE* in = fopen(argv[2], "rb");
		FILE* out = fopen(argv[3], "wb");
		if (in == NULL) {
			fprintf(out, "Cant open file in.txt \n");
		}
		else {
			decode_int(in, out);
		}
		if (in == 0) {
			fclose(out);
			return 0;
		}
		fclose(in);
		fclose(out);
		return 0;
	}*/
														//tester	
	FILE* in = fopen("in.txt", "rb");
	FILE* out = fopen("out.txt", "wb");
	if (in == NULL) {
		fprintf(out, "Cant open file in.txt \n");
	}
	else {
		int mode = fgetc(in);
		if (mode == 'c') {
			encode(in, out);
		}
		if (mode == 'd') {
			decode(in, out);
		}
	}
	if (in == 0) {
		fclose(out);
		return 0;
	}
	fclose(in);
	fclose(out);
	return 0;
}