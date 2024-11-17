#ifndef ARTIST_H
#define ARTIST_H

#include "tree.h"

typedef struct Artist {
    int id;
    char name[50];
} Artist;

int compare_artist(void* a, void* b);
void print_artist(void* data);
void free_artist_data(void* data);
void export_artist(void* data, FILE* file);
Tree* add_artist(Tree* artist_tree, Artist* new_artist);
Tree* load_artists_from_json(const char* filename);

#endif
