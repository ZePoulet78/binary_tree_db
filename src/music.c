#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "music.h"
#include "artist.h"
#include "tree.h"

int compare_music(void* a, void* b) {
    Music* music_a = (Music*)a;
    Music* music_b = (Music*)b;
    return music_a->id - music_b->id;
}

void print_music(void* data) {
    Music* music = (Music*)data;
    printf("Music ID: %d, Title: %s, Duration: %u sec, Artist ID: %d\n",
           music->id, music->title, music->duration, music->artist_id);
}

void free_music_data(void* data) {
    Music* music = (Music*)data;
    free(music);
}

void export_music(void* data, FILE* file) {
    Music* music = (Music*)data;
    fprintf(file, "\"id\":%d,\"title\":\"%s\",\"duration\":%u,\"artist_id\":%d",
            music->id, music->title, music->duration, music->artist_id);
}

Tree* add_music(Tree* music_tree, Music* new_music) {
    if (search(music_tree, new_music, compare_music)) {
        printf("music with Id %d already exists\n", new_music->id);
        free(new_music);
        return music_tree;
    }
    return insert(music_tree, new_music, compare_music);
}

Tree* load_music_tree_from_json(struct json_object* json_node) {
    if (json_node == NULL || json_object_get_type(json_node) != json_type_object) {
        return NULL; 
    }

    
    Music* music = (Music*)malloc(sizeof(Music));
    music->id = json_object_get_int(json_object_object_get(json_node, "id"));
    strncpy(music->title, json_object_get_string(json_object_object_get(json_node, "title")), sizeof(music->title));
    music->duration = json_object_get_int(json_object_object_get(json_node, "duration"));
    music->artist_id = json_object_get_int(json_object_object_get(json_node, "artist_id"));

    
    Tree* node = create_node(music);

    
    struct json_object* left_node = json_object_object_get(json_node, "left");
    node->left = load_music_tree_from_json(left_node);

    
    struct json_object* right_node = json_object_object_get(json_node, "right");
    node->right = load_music_tree_from_json(right_node);

    
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    return node;
}
Tree* load_musics_from_json(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s.\n", filename);
        return NULL;
    }

    
    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* data = (char*)malloc(length + 1);
    fread(data, 1, length, file);
    fclose(file);

    
    struct json_object* parsed_json = json_tokener_parse(data);
    free(data);

    if (!parsed_json) {
        printf("Error: Could not parse JSON.\n");
        return NULL;
    }

    
    struct json_object* musics_array;
    if (!json_object_object_get_ex(parsed_json, "musics", &musics_array)) {
        printf("Error: Could not find 'musics' key in JSON.\n");
        return NULL;
    }

    
    Tree* music_tree = NULL;
    if (json_object_array_length(musics_array) > 0) {
        struct json_object* root_node = json_object_array_get_idx(musics_array, 0);
        music_tree = load_music_tree_from_json(root_node);
    }

    json_object_put(parsed_json); 
    return music_tree;
}