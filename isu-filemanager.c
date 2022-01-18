#include "isu-filemanager.h"
#include <stdio.h>

#define FILENAME_LENGTH 256

int main() {

    main_menu();

    return 0;
}

void main_menu() {

    int choice;
    const char file_name[FILENAME_LENGTH];

    printf("#######################\n");
    printf("##ISU File Manager##\n");
    printf("#######################\n");

    printf("Available Operations:\n");
    printf("1) Create file\n");
    printf("2) Delete file\n");
    printf("3) Rename file\n");
    printf("4) Copy file\n");
    printf("5) Move file\n");

    printf("Enter your choice [1-5]: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("\n\nEnter the name of the file: ");
        scanf("%s", file_name);
        create_file(file_name);
    }

}

void create_file(const char* file_name) {

    if (fopen(file_name, "r") != NULL) {
        fprintf(stderr, "File already exists!\n\n");
        main_menu();
    }

    if (fopen(file_name, "w") != NULL) {
        printf("File created successfully!\n");
    } else {
        fprintf(stderr, "An error occured while creating the file!\n\n");
        main_menu();
    }

}