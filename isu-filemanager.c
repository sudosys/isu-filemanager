#include "isu-filemanager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 512

FILE* file;

int main() {

    main_menu();

    return 0;
}

void main_menu() {

    char command[MAX_COMMAND_LENGTH];
    
    printf("#######################\n");
    printf("###ISU File Manager####\n");
    printf("#######################\n\n");

    printf("Enter desired command with respective parameters: ");
    fgets(command, MAX_COMMAND_LENGTH, stdin);

    split_run_command(command);

}

void split_run_command(char* command) {

    char* token = strtok(command, " ");
    int command_index = 0;
    char* command_pieces[3] = {'\0','\0','\0'};

    while (token != NULL) {

        command_pieces[command_index] = token;

        token = strtok(NULL, " ");
        command_index++;

    }

    if (strcmp(command_pieces[0], "create") == 0) {
        create_file(command_pieces[1]);
    } else if (strcmp(command_pieces[0], "delete") == 0) {
        delete_file(command_pieces[1]);
    } else if (strcmp(command_pieces[0], "rename") == 0) {
        rename_file(command_pieces[1],command_pieces[2]);
    } else if (strcmp(command_pieces[0], "copy") == 0) {
        copy_file(command_pieces[1],command_pieces[2]);
    }

}

void create_file(char* file_name) {

    file_name[strcspn(file_name, "\n")] = 0;

    printf("%s", file_name);
    
    file = fopen(file_name, "r");

    if (file != NULL) {
        fprintf(stderr, "File already exists!\n\n");
    }
    
    file = fopen(file_name, "w");

    if (file != NULL) {
        printf("File created successfully!\n\n");
    } else {
        fprintf(stderr, "An error occured while creating the file!\n\n");
    }

    fclose(file);

    main_menu();

}

void delete_file(char* file_name) {

    file_name[strcspn(file_name, "\n")] = 0;

    if (remove(file_name) == 0) {
        printf("File deleted successfully!\n\n");
    } else {
        fprintf(stderr, "An error occured while deleting the file!\n\n");
    }

    main_menu();

}

void rename_file(char* old_file_name, char* new_file_name) {

    new_file_name[strcspn(new_file_name, "\n")] = 0;

    if (rename(old_file_name, new_file_name) == 0) {
        printf("File renamed successfully!\n\n");
    } else {
        fprintf(stderr, "An error occured while renaming the file!\n\n");
    }

    main_menu();

}

void copy_file(char* file_name, char* copied_file_name) {
    
    copied_file_name[strcspn(copied_file_name, "\n")] = 0;

    char ch;
    FILE* copy_file;

    file = fopen(file_name, "r");

    if (file == NULL) {
        fprintf(stderr, "File does not exist!\n\n");
        main_menu();
    }

    copy_file = fopen(copied_file_name, "w");

    if (copy_file == NULL) {
        fprintf(stderr, "Copy file can't be created!\n\n");
        main_menu();
    }

    while ((ch = fgetc(file)) != EOF) {
        fputc(ch, copy_file);
    }

    printf("File copied successfully!\n\n");
}