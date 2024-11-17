#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

Tree* create_node(void* data) {
    Tree* new_node = (Tree*)malloc(sizeof(Tree));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    return new_node;
}

int height(Tree* node) {
    return node ? node->height : 0;
}

int get_balance(Tree* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

Tree* rotate_right(Tree* y) {
    Tree* x = y->left;
    Tree* T = x->right;
    x->right = y;
    y->left = T;
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    return x;
}

Tree* rotate_left(Tree* x) {
    Tree* y = x->right;
    Tree* T = y->left;
    y->left = x;
    x->right = T;
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    return y;
}

Tree* insert(Tree* root, void* data, int (*compare)(void*, void*)) {
    if (!root) return create_node(data);
    int cmp = compare(data, root->data);
    if (cmp < 0) {
        root->left = insert(root->left, data, compare);
    } else if (cmp > 0) {
        root->right = insert(root->right, data, compare);
    } else {
        return root;
    }
    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    int balance = get_balance(root);

    if (balance > 1 && compare(data, root->left->data) < 0) 
        return rotate_right(root);

    if (balance < -1 && compare(data, root->right->data) > 0)
        return rotate_left(root);

    if (balance > 1 && compare(data, root->left->data) > 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    if (balance < -1 && compare(data, root->right->data) < 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }
    
    return root;
}

Tree* find_min(Tree* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

Tree* delete_node(Tree* root, void* key, int (*compare)(void*, void*), void (*free_data)(void*)) {
    if (root == NULL) {
        return root; 
    }

    int cmp = compare(key, root->data);
    if (cmp < 0) {
        root->left = delete_node(root->left, key, compare, free_data);
    } else if (cmp > 0) {
        root->right = delete_node(root->right, key, compare, free_data);
    } else {
        
        if (root->left == NULL || root->right == NULL) {
            Tree* temp = root->left ? root->left : root->right;

            if (free_data) {
                free_data(root->data); 
            }
            free(root);

            return temp; 
        } else {
            
            Tree* temp = find_min(root->right);

            
            if (free_data) {
                free_data(root->data); 
            }
            root->data = temp->data;

            
            root->right = delete_node(root->right, temp->data, compare, NULL);
        }
    }

    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));
   
    int balance = get_balance(root);
    
    if (balance > 1 && get_balance(root->left) >= 0) {
        return rotate_right(root);
    }
    
    if (balance > 1 && get_balance(root->left) < 0) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    
    if (balance < -1 && get_balance(root->right) <= 0) {
        return rotate_left(root);
    }
    
    if (balance < -1 && get_balance(root->right) > 0) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

void* search(Tree* root, void* key, int (*compare)(void*, void*)) {
    if (root == NULL) return NULL;
    int cmp = compare(key, root->data);
    if (cmp < 0) {
        return search(root->left, key, compare);
    } else if (cmp > 0) {
        return search(root->right, key, compare);
    } else {
        return root->data;
    }
}

void display_tree_hierarchy(Tree* root, int depth, void (*print_data)(void*)) {
    if (!root) return;
    display_tree_hierarchy(root->right, depth + 1, print_data);
    for (int i = 0; i < depth; i++) printf("    ");
    print_data(root->data);
    display_tree_hierarchy(root->left, depth + 1, print_data);
}


void export_tree_to_json(Tree* root, FILE* file, void (*export_data)(void*, FILE*), int is_root) {
    if (!root) return;
   
    fprintf(file, "{");
    export_data(root->data, file); 
   
    fprintf(file, ",\"left\":");
    if (root->left) {
        export_tree_to_json(root->left, file, export_data, 0);
    } else {
        fprintf(file, "null");
    }

    fprintf(file, ",\"right\":");
    if (root->right) {
        export_tree_to_json(root->right, file, export_data, 0);
    } else {
        fprintf(file, "null");
    }

    fprintf(file, "}");
}
