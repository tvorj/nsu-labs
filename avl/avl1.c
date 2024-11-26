#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct tNode {
	int key;
	unsigned char height;
	struct tNode* left;
	struct tNode* right;
} node;

node* new_node(node* tree, int val) {
	tree = (node*)malloc(sizeof(node));
	if (tree == NULL) {
		return NULL;
	}
	tree->key = val;
	tree->height = 1;
	tree->left = tree->right = NULL;
	return tree;
}

int height(node* tree) {
	if (tree == NULL) {
		return 0;
	}
	else {
		return tree->height;
	}
}

void fix_height(node* tree) {
	int left_height = height(tree->left);
	int right_height = height(tree->right);
	if (left_height > right_height) {
		tree->height = left_height + 1;
	}
	else {
		tree->height = right_height + 1;
	}
}

node* left_rotate(node* tree) {
	node* tmp = tree->right;
	tree->right = tmp->left;
	tmp->left = tree;
	fix_height(tree);
	fix_height(tmp);
	return tmp;
}

node* right_rotate(node* tree) {
	node* tmp = tree->left;
	tree->left = tmp->right;
	tmp->right = tree;
	fix_height(tree);
	fix_height(tmp);
	return tmp;
}

node* update_balance(node* tree) {
	int b_factor = height(tree->right) - height(tree->left);
	if (b_factor == 2) {
		if (height(tree->right->left) > height(tree->right->right)) {
			tree->right = right_rotate(tree->right);
		}
		return left_rotate(tree);
	}
	if (b_factor == -2) {
		if (height(tree->left->right) > height(tree->left->left)) {
			tree->left = left_rotate(tree->left);
		}
		return right_rotate(tree);
	}
	return tree;
}

node* insert(node* tree, int val) {
	if (!tree) {
		return new_node(tree, val);
	}
	if (tree->key >= val) {
		tree->left = insert(tree->left, val);
	}
	else {
		tree->right = insert(tree->right, val);
	}
	fix_height(tree);
	return update_balance(tree);
}

void free_tree(node* tree) {
	if (!tree) {
		return;
	}
	if (tree->left) {
		free_tree(tree->left);
	}
	if (tree->right) {
		free_tree(tree->right);
	}
	free(tree);
}

void print(node* tree) {
	if (tree->left) {
		print(tree->left);
	}
	printf("%d %d \n", tree->key, tree->height);
	if (tree->right) {
		print(tree->right);
	}
}

int check(int argc, char* argv[]) {
	if (argc > 1) {
		if (argv[1][0] == '-' && argv[1][1] == 't') {
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

void print_tree(node* tree) {
	if (!tree) {
		return;
	}
	print_tree(tree->left);
	printf("%d ", tree->key);
	print_tree(tree->right);
}

int main(int argc, char* argv[]) {
	int n, val;
	node* tree = NULL;
	if (scanf("%d", &n) == 0) {
		return 0;
	}
	for (int i = 0; i < n; i++) {
		if (scanf("%d", &val) == 0) {
			return 0;
		}
		tree = insert(tree, val);
	}
	if (check(argc, argv) == 1) {
		print_tree(tree);
	}
	else {
		printf("%d ", height(tree));
	}
	free_tree(tree);
	return 0;
}
