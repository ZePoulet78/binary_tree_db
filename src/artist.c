#include <json-c/json.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "artist.h"
#include "tree.h"

int compare_artist(void* a, void* b) {
    Artist* artist_a = (Artist*)a;
    Artist* artist_b = (Artist*)b;
    return artist_a->id - artist_b->id;
}

void print_artist(void* data) {
    Artist* artist = (Artist*)data;
    printf("Artist ID: %d, Name: %s\n", artist->id, artist->name);
}

void free_artist_data(void* data) {
    Artist* artist = (Artist*)data;
    free(artist);
}

void export_artist(void* data, FILE* file) {
    Artist* artist = (Artist*)data;
    fprintf(file, "\"id\":%d,\"name\":\"%s\"", artist->id, artist->name);
}

Tree* add_artist(Tree* artist_tree, Artist* new_artist) {
    if (search(artist_tree, new_artist, compare_artist)) {
        printf("Error: An artist with ID %d already exists.\n", new_artist->id);
        free(new_artist);
        return artist_tree;
    }
    return insert(artist_tree, new_artist, compare_artist);
}

Tree* load_artist_tree_from_json(struct json_object* json_node) {
    if (!json_node || json_object_get_type(json_node) != json_type_object) {
        return NULL;
    }

    Artist* artist = (Artist*)malloc(sizeof(Artist));
    artist->id = json_object_get_int(json_object_object_get(json_node, "id"));
    strncpy(artist->name, json_object_get_string(json_object_object_get(json_node, "name")), sizeof(artist->name));

    Tree* node = create_node(artist);

    struct json_object* left_node = json_object_object_get(json_node, "left");
    node->left = load_artist_tree_from_json(left_node);

    struct json_object* right_node = json_object_object_get(json_node, "right");
    node->right = load_artist_tree_from_json(right_node);

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    return node;
}

Tree* load_artists_from_json(const char* filename) {
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

    struct json_object* artists_array;
    if (!json_object_object_get_ex(parsed_json, "artists", &artists_array)) {
        printf("Error: Could not find 'artists' key in JSON.\n");
        json_object_put(parsed_json);
        return NULL;
    }

    Tree* artist_tree = NULL;
    if (json_object_array_length(artists_array) > 0) {
        struct json_object* root_node = json_object_array_get_idx(artists_array, 0);
        artist_tree = load_artist_tree_from_json(root_node);
    }

    json_object_put(parsed_json);
    return artist_tree;
}
