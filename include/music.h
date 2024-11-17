#ifndef MUSIC_H
#define MUSIC_H

#include "tree.h"

typedef struct Music {
    int id;
    char title[100];
    unsigned int duration;
    int artist_id;
} Music;

int compare_music(void* a, void* b);
void print_music(void* data);
void free_music_data(void* data);
void export_music(void* data, FILE* file);
Tree* add_music(Tree* music_tree, Music* new_music);
Tree* load_musics_from_json(const char* filename);


#endif
