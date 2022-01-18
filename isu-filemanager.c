#include "isu-filemanager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 512

FILE* file;

int main() {

    prompt();

    return 0;
}

void prompt() {

    char command[MAX_COMMAND_LENGTH];
    fgets(command, MAX_COMMAND_LENGTH, '\0');

    printf("ISU File Manager #> ");
    fgets(command, MAX_COMMAND_LENGTH, stdin);

    split_run_command(command);

}

void split_run_command(char* command) {

    char* token = strtok(command, " ");
    int command_index = 0;
    char* command_pieces[3];

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
    } else if (strcmp(command_pieces[0], "move") == 0) {
        move_file(command_pieces[1],command_pieces[2]);
    }

}

void create_file(char* file_name) {

    file_name[strcspn(file_name, "\n")] = 0;
    
    file = fopen(file_name, "r");

    if (file != NULL) {
        fprintf(stderr, "File already exists!\n\n");
        prompt();
    }
    
    file = fopen(file_name, "w");

    if (file != NULL) {
        printf("File created successfully!\n\n");
        prompt();
    } else {
        fprintf(stderr, "An error occured while creating the file!\n\n");
        prompt();
    }

    fclose(file);

}

void delete_file(char* file_name) {

    file_name[strcspn(file_name, "\n")] = 0;

    if (remove(file_name) == 0) {
        printf("File deleted successfully!\n\n");
    } else {
        fprintf(stderr, "An error occured while deleting the file!\n\n");
    }

    prompt();

}

void rename_file(char* old_file_name, char* new_file_name) {

    new_file_name[strcspn(new_file_name, "\n")] = 0;

    if (rename(old_file_name, new_file_name) == 0) {
        printf("File renamed successfully!\n\n");
    } else {
        fprintf(stderr, "An error occured while renaming the file!\n\n");
    }

    prompt();

}

void copy_file(char* file_name, char* copied_file_name) {
    
    copied_file_name[strcspn(copied_file_name, "\n")] = 0;

    char ch;
    FILE* copy_file;

    file = fopen(file_name, "r");

    if (file == NULL) {
        fprintf(stderr, "File does not exist!\n\n");
        prompt();
    }

    copy_file = fopen(copied_file_name, "w");

    if (copy_file == NULL) {
        fprintf(stderr, "Copy file can't be created!\n\n");
        prompt();
    }

    while ((ch = fgetc(file)) != EOF) {
        fputc(ch, copy_file);
    }

    printf("File copied successfully!\n\n");
}

void move_file(char* file_name, char* destination) {

    destination[strcspn(destination, "\n")] = 0;

    if (rename(file_name, destination) == 0) {
        printf("File moved successfully!\n\n");
    } else {
        fprintf(stderr, "An error occured while moving the file!\n\n");
    }

    prompt();

}