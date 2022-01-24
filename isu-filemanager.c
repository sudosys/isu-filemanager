#include "isu-filemanager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 512
#define MAX_TEXT_LENGTH 256
#define TRUE 1
#define FALSE 0

FILE* file;

int main() {

    prompt();

    return 0;
}

void prompt() {

    char command[MAX_COMMAND_LENGTH];

    printf("ISU File Manager $> ");
    fgets(command, MAX_COMMAND_LENGTH, stdin);

    command[strcspn(command, "\n")] = 0;

    run_command(command);

}

void run_command(char* command) {

    char* token = strtok(command, " ");
    int command_index = 0;
    const char* command_pieces[3] = {NULL, NULL, NULL};

    while (token != NULL) {

        command_pieces[command_index] = token;

        token = strtok(NULL, " ");
        command_index++;

    }

    if (strcmp(command_pieces[0], "exit") == 0) { exit(EXIT_SUCCESS); }

    if (strcmp(command_pieces[0], "create") == 0) {

        if (command_pieces[2] != NULL) {
            fprintf(stderr, "Invalid create command.\ncreate /h for help.\n\n");
            prompt();
        } else if (strcmp(command_pieces[1], "/h") == 0) {
            printf("It creates the file.\nUsage: create <file_name>\n\n");
            prompt();
        } else { create_file(command_pieces[1]); }

    } else if (strcmp(command_pieces[0], "delete") == 0) {

        if (command_pieces[2] != NULL) {
            fprintf(stderr, "Invalid delete command.\ndelete /h for help.\n\n");
            prompt();
        } else if (strcmp(command_pieces[1], "/h") == 0 ){
            printf("It deletes the file.\nUsage: delete <file_name>\n\n");
            prompt();
        } else { delete_file(command_pieces[1]); }

    } else if (strcmp(command_pieces[0], "rename") == 0) {

        if (command_pieces[2] == NULL) {
            fprintf(stderr, "Invalid rename command.\nrename /h for help.\n\n");
            prompt();
        } else if (strcmp(command_pieces[1], "/h") == 0 ){
            printf("It renames the file.\nUsage: rename <old_file_name> <new_file_name>\n\n");
            prompt();
        } else { rename_file(command_pieces[1], command_pieces[2]); }

    } else if (strcmp(command_pieces[0], "copy") == 0) {

        if (command_pieces[2] == NULL) {
            fprintf(stderr, "Invalid copy command.\ncopy /h for help.\n\n");
            prompt();
        } else if (strcmp(command_pieces[1], "/h") == 0 ){
            printf("It copies the file.\nUsage: copy <file_name> <copied_file_name (along with the directory if it going to be copied to somewhere else.)>\n\n");
            prompt();
        } else { copy_file(command_pieces[1], command_pieces[2]); }

    } else if (strcmp(command_pieces[0], "move") == 0) {

        if (command_pieces[2] == NULL) {
            fprintf(stderr, "Invalid move command.\nmove /h for help.\n\n");
            prompt();
        } else if (strcmp(command_pieces[1], "/h") == 0 ){
            printf("It moves the file.\nUsage: move <file_name> <destination_path>\n\n");
            prompt();
        } else { delete_file(command_pieces[1]); }

    } else if (strcmp(command_pieces[0], "append") == 0) {

        if (command_pieces[2] != NULL){
            fprintf(stderr, "Invalid append command.\nappend /h for help.\n\n");
            prompt();
        } else if (strcmp(command_pieces[1], "/h") == 0 ){
            printf("It appends text into the file.\nUsage: append <file_name>\nAfter <enter> has pressed user should input the text that is going to be appended to the file.\n\n");
            prompt();
        } else { append_file(command_pieces[1]); }

    } else if (strcmp(command_pieces[0], "insert") == 0) {

        if (command_pieces[2] != NULL){
            fprintf(stderr, "Invalid insert command.\ninsert /h for help.\n\n");
            prompt();
        } else if (strcmp(command_pieces[1], "/h") == 0 ){
            printf("It inserts the text into the file.\nUsage: insert <file_name> <which_point_to_insert (as number of characters starting from 1.)>\n\n");
            prompt();
        } else { insert_file(command_pieces[1], atoi(command_pieces[2])); }

    } else if (strcmp(command_pieces[0], "clear") == 0) {

        if (command_pieces[2] != NULL){
            fprintf(stderr, "Invalid clear command.\n\n");
            prompt();
        } else if (strcmp(command_pieces[1], "/h") == 0 ){
            printf("It deletes all the content in the file.\nUsage: clear <file_name>\n\n");
            prompt();
        } else { clear_file(command_pieces[1]); }

    } else if (strcmp(command_pieces[0], "scroll") == 0) {

        if (command_pieces[2] == NULL){
            fprintf(stderr, "Invalid scroll command.\n\n");
            prompt();
        } else if (strcmp(command_pieces[1], "/h") == 0 ){
            printf("It displays the file content page by page. The number of rows in a page should be specified by the user.\nUsage: scroll <file_name> <number_of_rows_in_a_page>\n\n");
            prompt();
        } else { scroll_file(command_pieces[1], atoi(command_pieces[2])); }

    } else {
        printf("Invalid input!\n\n");
        prompt();
    }

}

void create_file(const char* file_name) {

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

void delete_file(const char* file_name) {

    if (remove(file_name) == 0) {
        printf("File deleted successfully!\n\n");
    } else {
        fprintf(stderr, "An error occured while deleting the file!\n\n");
    }

    prompt();

}

void rename_file(const char* old_file_name, const char* new_file_name) {

    if (rename(old_file_name, new_file_name) == 0) {
        printf("File renamed successfully!\n\n");
    } else {
        fprintf(stderr, "An error occured while renaming the file!\n\n");
    }

    prompt();

}

void copy_file(const char* file_name, const char* copied_file_name) {

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

    fclose(file);
    fclose(copy_file);

    printf("File copied successfully!\n\n");

    prompt();
}

void move_file(const char* file_name, const char* destination) {

    if (rename(file_name, destination) == 0) {
        printf("File moved successfully!\n\n");
    } else {
        fprintf(stderr, "An error occured while moving the file!\n\n");
    }

    prompt();

}

void append_file(const char* file_name) {

    char text_to_append[MAX_TEXT_LENGTH];
    char* token;

    file = fopen(file_name, "a");

    if (file == NULL) {
        fprintf(stderr, "File does not exist!\n\n");
        prompt();
    }

    printf("Enter the text to append: ");
    fgets(text_to_append, MAX_TEXT_LENGTH, stdin);

    text_to_append[strcspn(text_to_append, "\n")] = 0;

    token = strtok(text_to_append, " ");

    while (token != NULL) {

        fputs(token, file);
        fputs(" ", file);

        token = strtok(NULL, " ");

    }

    fputs("\n", file);

    fclose(file);

    printf("Append to file is successful!\n\n");

    prompt();

}

void insert_file(const char* file_name, int insertion_pos) {

    char text_to_insert[MAX_TEXT_LENGTH];
    char text_before_insertion_pos[insertion_pos+1];
    char text_after_insertion_pos[MAX_TEXT_LENGTH];
    char ch;
    int pos_index = 0;
    int after_index = 0;

    for (int i = 0; i < insertion_pos+1; i++) { text_before_insertion_pos[i] = '\0'; }
    for (int i = 0; i < MAX_TEXT_LENGTH; i++) { text_after_insertion_pos[i] = '\0'; }

    file = fopen(file_name, "r");

    if (file == NULL) {
        fprintf(stderr, "File could not be opened!");
        prompt();
    }

    printf("Enter the text to insert: ");
    fgets(text_to_insert, MAX_TEXT_LENGTH, stdin);

    text_to_insert[strcspn(text_to_insert, "\n")] = 0;

    while (pos_index < insertion_pos) {

        ch = fgetc(file);

        text_before_insertion_pos[pos_index] = ch;

        pos_index++;

    }

    while ((ch = fgetc(file)) != EOF) {

        text_after_insertion_pos[after_index] = ch;

        after_index++;

    }

    file = fopen(file_name, "w");

    if (file == NULL) {
        fprintf(stderr, "File could not be opened!");
        prompt();
    }

    fputs(text_before_insertion_pos, file);
    fputs(text_to_insert, file);
    fputs(text_after_insertion_pos, file);

    fclose(file);

    printf("Text inserted into specified position in the file successfully!\n\n");

    prompt();

}

int does_file_exist(const char* file_name) {

    file = fopen(file_name, "r");

    if (file != NULL) {
        fclose(file);
        return TRUE;
    }

    return FALSE;

}

void clear_file(const char* file_name) {

    if (!does_file_exist(file_name)) {
        fprintf(stderr, "File does not exist!\n\n");
        prompt();
    }

    file = fopen(file_name, "w");

    if (file == NULL) {
        fprintf(stderr, "Error occured while trying to clear the content of the file!\n\n");
    } else {
        printf("File content cleared successfully!\n\n");
    }

    prompt();

    fclose(file);

}

void scroll_file(const char* file_name, int row_count){

    int row_index=0;

    char array[MAX_TEXT_LENGTH];

    file = fopen(file_name, "r");

    if (file == NULL) {
        fprintf(stderr, "Error occured while trying to scroll the content of the file!\n\n");
    }

    while(fgets (array, MAX_TEXT_LENGTH, file) !=NULL){
            
            if(row_index==row_count){
                row_index=0;
                getchar();
            }

            printf("%s", array);
            row_index++;
    }
    
    printf("\n");
    prompt();

    fclose(file);

}