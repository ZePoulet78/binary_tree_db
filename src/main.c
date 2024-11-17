#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"
#include "artist.h"
#include "music.h"


int get_menu_choice() {
    char input[10];
    int choice;

    printf("Choose an option: ");
    if (fgets(input, sizeof(input), stdin) == NULL) {
        printf("Error reading input.\n");
        return -1;
    }

    input[strcspn(input, "\n")] = 0;
    
    if (sscanf(input, "%d", &choice) != 1) {
        printf("Please entre a valid number\n");
        return -1;
    }

    return choice;
}




int main() {
    Tree* artist_tree = NULL; 
    Tree* music_tree = NULL;  

    int id, artist_id;
    char name[50], title[100];
    unsigned int duration;

    while (1) {
        printf("\n----------------- Menu -----------------\n");
        printf("1. Add Artist\n");
        printf("2. Add Music\n");
        printf("3. Show Artists\n");
        printf("4. Show Musics\n");
        printf("5. Search Artist by ID\n");
        printf("6. Search Music by ID\n");
        printf("7. Remove Artist\n");
        printf("8. Remove Music\n");
        printf("9. Display Trees (Hierarchical View)\n");
        printf("10. Save to JSON\n");
        printf("11. Load from JSON\n");
        printf("12. Exit\n");
        printf("----------------------------------------\n");
        int choice = get_menu_choice();
        if (choice == -1) {
            continue; 
        }

        switch (choice) {
            case 1:
                printf("Enter Artist ID: ");
                scanf("%d", &id);
                printf("Enter Artist Name: ");
                scanf("%s", name);

                Artist* new_artist = (Artist*)malloc(sizeof(Artist));
                new_artist->id = id;
                strncpy(new_artist->name, name, sizeof(new_artist->name));

                artist_tree = add_artist(artist_tree, new_artist);
                printf("Artist added successfully!\n");
                break;

            case 2:
                printf("Enter Music ID: ");
                scanf("%d", &id);
                printf("Enter Music Title: ");
                scanf("%s", title);
                printf("Enter Music Duration (seconds): ");
                scanf("%u", &duration);
                printf("Enter Artist ID: ");
                scanf("%d", &artist_id);

                Artist search_artist_key = {artist_id, ""};
                if (!search(artist_tree, &search_artist_key, compare_artist)) {
                    printf("Error: Artist with ID %d does not exist.\n", artist_id);
                    break;
                }

                Music* new_music = (Music*)malloc(sizeof(Music));
                new_music->id = id;
                strncpy(new_music->title, title, sizeof(new_music->title));
                new_music->duration = duration;
                new_music->artist_id = artist_id;

                music_tree = add_music(music_tree, new_music);
                printf("Music added successfully!\n");
                break;

            case 3:
                printf("Artists:\n");
                display_tree_hierarchy(artist_tree, 0, print_artist);
                break;

            case 4:
                printf("Musics:\n");
                display_tree_hierarchy(music_tree, 0, print_music);
                break;

            case 5:
                printf("Enter Artist ID to search: ");
                scanf("%d", &id);

                Artist search_artist = {id, ""};
                Artist* found_artist = (Artist*)search(artist_tree, &search_artist, compare_artist);

                if (found_artist) {
                    printf("Artist found: ID: %d, Name: %s\n", found_artist->id, found_artist->name);
                } else {
                    printf("Artist with ID %d not found.\n", id);
                }
                break;

            case 6:
                printf("Enter Music ID to search: ");
                scanf("%d", &id);

                Music search_music = {id, "", 0, 0};
                Music* found_music = (Music*)search(music_tree, &search_music, compare_music);

                if (found_music) {
                    printf("Music found: ID: %d, Title: %s, Duration: %u sec, Artist ID: %d\n",
                           found_music->id, found_music->title, found_music->duration, found_music->artist_id);
                } else {
                    printf("Music with ID %d not found.\n", id);
                }
                break;

            case 7:
                printf("Enter Artist ID to remove: ");
                scanf("%d", &id);

                Artist search_artist_removal = {id, ""};
                artist_tree = delete_node(artist_tree, &search_artist_removal, compare_artist, free_artist_data);
                printf("Artist with ID %d removed.\n", id);
                break;

            case 8:
                printf("Enter Music ID to remove: ");
                scanf("%d", &id);

                Music search_music_removal = {id, "", 0, 0};
                music_tree = delete_node(music_tree, &search_music_removal, compare_music, free_music_data);
                printf("Music with ID %d removed.\n", id);
                break;

            case 9:
                printf("\nArtists Tree:\n");
                display_tree_hierarchy(artist_tree, 0, print_artist);
                printf("\nMusics Tree:\n");
                display_tree_hierarchy(music_tree, 0, print_music);
                break;

            case 10: {
                FILE* file = fopen("data/database.json", "w");
                if (!file) {
                    printf("Error: Could not open file for writing.\n");
                    break;
                }

                fprintf(file, "{\n\"artists\":[");

                if (artist_tree) {
                    export_tree_to_json(artist_tree, file, export_artist, 1);
                }

                fprintf(file, "],\n\"musics\":[");

                if (music_tree) {
                    export_tree_to_json(music_tree, file, export_music, 1);
                }

                fprintf(file, "]\n}\n");

                fclose(file);
                printf("Database saved to 'data/database.json'.\n");
                break;
            }

            case 11:
                artist_tree = load_artists_from_json("data/database.json");
                music_tree = load_musics_from_json("data/database.json");
                printf("Database loaded from 'data/database.json'.\n");
                break;

            case 12:
                printf("Goodbye!\n");
                return 0;

            default:
                printf("Invalid option. Please try again.\n");
        }
    }
}
