#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct tNode{
    char height;
    char b_factor;
    int val;
    struct tNode* right;
    struct tNode* left;
}node; 


typedef struct tForest{
    int count;
    node* tree;
} forest;


void print_tree(node* tree) {
    if (tree == NULL) {
        return;
    }
    print_tree(tree->left);
    printf("%d", tree->val);
    print_tree(tree->right);
    return;
}


node* new_node(int val, forest* Forest) {
    Forest->count++;
    node* Tree = &Forest->tree[Forest->count - 1];
    Tree->height = 1;
    Tree->b_factor = 0;
    Tree->val = val;
    Tree->left = Tree->right = NULL;
    return Tree;
}


int height(node* tree) {
    if (tree == NULL) {
        return 0;
    }
    else {
        return tree->height;
    }
}


int balance_factor(node* tree) {
    if (tree == NULL) {
        return 0;
    }
    return tree->b_factor;
}


void fix_height(node* tree) {
    if (tree == NULL) {
        return;
    }
    if (height(tree->left) >= height(tree->right)) {
        tree->height = height(tree->left) + 1;
    }
    else {
        tree->height = height(tree->right) + 1;
    }
    tree->b_factor = height(tree->right) - height(tree->left);
}


node* right_rotate(node* tree) {
    node* tmp = tree->left;
    tree->left = tmp->right;
    tmp->right = tree;
    fix_height(tree);
    fix_height(tmp);
    return tmp;
}


node* left_rotate(node* tree) {
    node* tmp = tree->right;
    tree->right = tmp->left;
    tmp->left = tree;
    fix_height(tree);
    fix_height(tmp);
    return tmp;
}


node* update_balance(node* tree) { 
    fix_height(tree);
    if (balance_factor(tree) == 2) {
        if (balance_factor(tree->right) < 0) {
            tree->right = right_rotate(tree->right);
        }
        return left_rotate(tree);
    }
    else {
        if (balance_factor(tree) == -2) {
            if (balance_factor(tree->left) > 0) {
                tree->left = left_rotate(tree->left);
            }
            return right_rotate(tree);
        }
    }
    return tree;
}


void insert(node** tree, forest* Forest, int val) {
    if (*tree == NULL) {
        *tree = new_node(val, Forest);
    }
    else {
        if (val < (*tree)->val) {
            insert(&(*tree)->left, Forest, val);
        }
        else {
            insert(&(*tree)->right, Forest, val);
        }
        *tree = update_balance(*tree);
    }
}
//
//
//void free_tree(node* tree) {
//    if (!tree) {
//        return;
//    }
//    if (tree->left) {
//        free_tree(tree->left);
//    }
//    if (tree->right) {
//        free_tree(tree->right);
//    }
//    free(tree);
//}
//

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


int main(int argc, char* argv[]) {
    int n;
    if (scanf("%d", &n) == 0) {
        return 0;
    }
    forest Forest = { 0, NULL };
    Forest.tree = malloc(n * sizeof(*Forest.tree));
    node* tree = NULL;
    for (int i = 0; i < n; i++) {
        int val;
        if (scanf("%d", &val) == 0) {
            free(Forest.tree);
            return 0;
        }
        insert(&tree, &Forest, val);
    }
    if (check(argc, argv) == 1) {
        print_tree(tree);
    }
    else {
        printf("%d", height(tree));
    }
    free(Forest.tree);
    return 0;
}
