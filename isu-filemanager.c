#include "isu-filemanager.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_FILENAME_LENGTH 256

FILE* file;

int main() {

    main_menu();

    return 0;
}

void main_menu() {

    int choice;
    
    printf("#######################\n");
    printf("###ISU File Manager##\n");
    printf("#######################\n");

    printf("Available Operations:\n");
    printf("1) Create file\n");
    printf("2) Delete file\n");
    printf("3) Rename file\n");
    printf("4) Copy file\n");
    printf("5) Move file\n");
    printf("6) Exit\n");

    printf("Enter your choice [1-5]: ");
    scanf("%d", &choice);

    if (choice == 6) { exit(EXIT_SUCCESS); }

    if (choice == 1) { create_file(); }
    else if (choice == 2) { delete_file(); }
    else if (choice == 3) { rename_file(); }

}

void create_file() {

    const char file_name[MAX_FILENAME_LENGTH];

    printf("Enter the name of the file: ");
    scanf("%s", file_name);

    file = fopen(file_name, "r");

    if (file != NULL) {
        fprintf(stderr, "File already exists!\n\n");
    }

    file = fopen(file_name, "w");

    if (file != NULL) {
        printf("File created successfully!\n");
    } else {
        fprintf(stderr, "An error occured while creating the file!\n\n");
    }

    fclose(file);

    main_menu();

}

void delete_file() {

    const char file_name[MAX_FILENAME_LENGTH];

    printf("Enter the name of the file: ");
    scanf("%s", file_name);

    if (remove(file_name) == 0) {
        printf("File deleted successfully!\n");
    } else {
        fprintf(stderr, "An error occured while deleting the file!\n\n");
    }

    main_menu();

}

void rename_file() {

    const char old_file_name[MAX_FILENAME_LENGTH], new_file_name[MAX_FILENAME_LENGTH];

    printf("Enter the name of the file to be renamed: ");
    scanf("%s", old_file_name);

    printf("Enter the new name of the file: ");
    scanf("%s", new_file_name);

    if (rename(old_file_name, new_file_name) == 0) {
        printf("File renamed successfully!\n");
    } else {
        fprintf(stderr, "An error occured while renaming the file!\n\n");
    }

    main_menu();

}