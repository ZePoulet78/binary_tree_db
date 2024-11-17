#ifndef TREE_H
#define TREE_H

typedef struct Tree {
    void* data;
    struct Tree* left;
    struct Tree* right;
    int height;
} Tree;

Tree* create_node(void* data);
int height(Tree* node);
int get_balance(Tree* node);
Tree* rotate_right(Tree* y);
Tree* rotate_left(Tree* x);
Tree* insert(Tree* root, void* data, int (*compare)(void*, void*));
Tree* delete_node(Tree* root, void* key, int (*compare)(void*, void*), void (*free_data)(void*));
void* search(Tree* root, void* key, int (*compare)(void*, void*));
void display_tree_hierarchy(Tree* root, int depth, void (*print_data)(void*));
void export_tree_to_json(Tree* root, FILE* file, void (*export_data)(void*, FILE*), int is_root);

#endif
