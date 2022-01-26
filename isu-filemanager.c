#include "isu-filemanager.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// macros for maximum command and text length are defined
#define MAX_COMMAND_LENGTH 256
#define MAX_TEXT_LENGTH 512
#define TRUE 1
#define FALSE 0

// global FILE*
FILE* file;

int main() {

    // file manager initalized by calling the prompt
    prompt();

    return 0;

}

void prompt() {

    char command[MAX_COMMAND_LENGTH];

    // command input taken here
    printf("ISU File Manager $> ");
    fgets(command, MAX_COMMAND_LENGTH, stdin);

    // trailing new line character (\n) is truncated
    command[strcspn(command, "\n")] = 0;

    run_command(command);

}

void run_command(char* command) {

    // given command is splitted by spaces using strtok from C STL
    char* token = strtok(command, " ");
    int command_index = 0;
    // splitted command will be saved inside this const char array
    const char* command_pieces[3] = {NULL, NULL, NULL};

    // command gets splitted here
    while (token != NULL) {

        command_pieces[command_index] = token;

        token = strtok(NULL, " ");
        command_index++;

    }

    // appropriate action taken according to the given command

    if (strcmp(command_pieces[0], "exit") == 0) { exit(EXIT_SUCCESS); }

    if (strcmp(command_pieces[0], "create") == 0) {

        if (command_pieces[2] != NULL) {
            fprintf(stderr, "Invalid create command.\ncreate /h for help.\n\n");
            prompt();
        } else if (strcmp(command_pieces[1], "/h") == 0) {
            printf("It creates a file.\nUsage: create <file_name>\n\n");
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

        if (command_pieces[2] == NULL && strcmp(command_pieces[1], "/h") != 0) {
            fprintf(stderr, "Invalid rename command.\nrename /h for help.\n\n");
            prompt();
        } else if (strcmp(command_pieces[1], "/h") == 0){
            printf("It renames the file.\nUsage: rename <old_file_name> <new_file_name>\n\n");
            prompt();
        } else { rename_file(command_pieces[1], command_pieces[2]); }

    } else if (strcmp(command_pieces[0], "copy") == 0) {

        if (command_pieces[2] == NULL && strcmp(command_pieces[1], "/h") != 0) {
            fprintf(stderr, "Invalid copy command.\ncopy /h for help.\n\n");
            prompt();
        } else if (strcmp(command_pieces[1], "/h") == 0 ){
            printf("It copies the file.\nUsage: copy <file_name> <copied_file_name>\nCopied file name can be written along with the directory if it is going to be copied to somewhere else.\n\n");
            prompt();
        } else { copy_file(command_pieces[1], command_pieces[2]); }

    } else if (strcmp(command_pieces[0], "move") == 0) {

        if (command_pieces[2] == NULL && strcmp(command_pieces[1], "/h") != 0) {
            fprintf(stderr, "Invalid move command.\nmove /h for help.\n\n");
            prompt();
        } else if (strcmp(command_pieces[1], "/h") == 0 ){
            printf("It moves the file.\nUsage: move <file_name> <destination_path>\n\n");
            prompt();
        } else { move_file(command_pieces[1], command_pieces[2]); }

    } else if (strcmp(command_pieces[0], "append") == 0) {

        if (command_pieces[2] != NULL){
            fprintf(stderr, "Invalid append command.\nappend /h for help.\n\n");
            prompt();
        } else if (strcmp(command_pieces[1], "/h") == 0 ){
            printf("It appends text into the file.\nUsage: append <file_name>\nAfter <enter> has pressed user should input the text that is going to be appended to the file.\n\n");
            prompt();
        } else { append_file(command_pieces[1]); }

    } else if (strcmp(command_pieces[0], "insert") == 0) {

        if (command_pieces[2] == NULL && strcmp(command_pieces[1], "/h") != 0){
            fprintf(stderr, "Invalid insert command.\ninsert /h for help.\n\n");
            prompt();
        } else if (strcmp(command_pieces[1], "/h") == 0 ){
            printf("It inserts the text into the file.\nUsage: insert <file_name> <point_to_insert>\nInsertion point is number of characters starting from 0.\n\n");
            prompt();
        } else { insert_file(command_pieces[1], atoi(command_pieces[2])); }

    } else if (strcmp(command_pieces[0], "clear") == 0) {

        if (command_pieces[2] != NULL){
            fprintf(stderr, "Invalid clear command.\nclear /h for help.\n\n");
            prompt();
        } else if (strcmp(command_pieces[1], "/h") == 0 ){
            printf("It deletes all the content in the file.\nUsage: clear <file_name>\n\n");
            prompt();
        } else { clear_file(command_pieces[1]); }

    } else if (strcmp(command_pieces[0], "scroll") == 0) {

        if (command_pieces[2] == NULL && strcmp(command_pieces[1], "/h") != 0){
            fprintf(stderr, "Invalid scroll command.\nscroll /h for help.\n\n");
            prompt();
        } else if (strcmp(command_pieces[1], "/h") == 0 ){
            printf("It displays the file content page by page.\nUsage: scroll <file_name> <number_of_rows_per_page>\nThe number of rows in a page should be specified by the user. Press <enter> to view the next page.\n\n");
            prompt();
        } else { scroll_file(command_pieces[1], atoi(command_pieces[2])); }

    } else {
        printf("Invalid input!\n\n");
        prompt();
    }

}

int does_file_exist(const char* file_name) {

    file = fopen(file_name, "r");

    if (file != NULL) {
        fclose(file);
        return TRUE;
    }

    return FALSE;

}

void create_file(const char* file_name) {

    if (does_file_exist(file_name)) {
        fprintf(stderr, "File already exists!\n\n");
        prompt();
    }

    // to create an empty file we open the given file_name in "w" mode
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

    if (!does_file_exist(file_name)) {
        fprintf(stderr, "File does not exist!\n\n");
        prompt();
    }

    // remove function from C STL returns 0 on successful operation
    if (remove(file_name) == 0) {
        printf("File deleted successfully!\n\n");
    } else {
        fprintf(stderr, "An error occured while deleting the file!\n\n");
    }

    prompt();

}

void rename_file(const char* old_file_name, const char* new_file_name) {

    if (!does_file_exist(old_file_name)) {
        fprintf(stderr, "File does not exist!\n\n");
        prompt();
    }

    // rename function from C STL returns 0 on successful operation
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

    if (!does_file_exist(file_name)) {
        fprintf(stderr, "File does not exist!\n\n");
        prompt();
    }

    file = fopen(file_name, "r");

    // create copied file
    copy_file = fopen(copied_file_name, "w");

    if (copy_file == NULL) {
        fprintf(stderr, "Copy file can't be created!\n\n");
        prompt();
    }

    // write source file contente character by character to copied file
    while ((ch = fgetc(file)) != EOF) { fputc(ch, copy_file); }

    fclose(file);
    fclose(copy_file);

    printf("File copied successfully!\n\n");

    prompt();
}

void move_file(const char* file_name, const char* destination) {

    if (!does_file_exist(file_name)) {
        fprintf(stderr, "File does not exist!\n\n");
        prompt();
    }

    // move command implemented using rename function from C STL
    if (rename(file_name, destination) == 0) {
        printf("File moved successfully!\n\n");
    } else {
        fprintf(stderr, "An error occured while moving the file!\n\n");
    }

    prompt();

}

void append_file(const char* file_name) {

    if (!does_file_exist(file_name)) {
        fprintf(stderr, "File does not exist!\n\n");
        prompt();
    }

    char text_to_append[MAX_TEXT_LENGTH];
    char* token;

    file = fopen(file_name, "a");

    if (file == NULL) {
        fprintf(stderr, "File could not be opened for appending!\n\n");
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

    if (!does_file_exist(file_name)) {
        fprintf(stderr, "File does not exist!");
        prompt();
    }

    file = fopen(file_name, "r");

    // fill char arrays with "\0"
    for (int i = 0; i < insertion_pos+1; i++) { text_before_insertion_pos[i] = '\0'; }
    for (int i = 0; i < MAX_TEXT_LENGTH; i++) { text_after_insertion_pos[i] = '\0'; }

    printf("Enter the text to insert: ");
    fgets(text_to_insert, MAX_TEXT_LENGTH, stdin);

    // truncate "\n" at the end of text_to_insert
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

    // write content before insertion to file
    fputs(text_before_insertion_pos, file);
    // write inserted content to file
    fputs(text_to_insert, file);
    // write content after insertion to file
    fputs(text_after_insertion_pos, file);

    fclose(file);

    printf("Text inserted into specified position in the file successfully!\n\n");

    prompt();

}

void clear_file(const char* file_name) {

    if (!does_file_exist(file_name)) {
        fprintf(stderr, "File does not exist!\n\n");
        prompt();
    }

    // file opened in "w" mode to clear the content of the file
    file = fopen(file_name, "w");

    if (file == NULL) {
        fprintf(stderr, "Error occured while trying to clear the content of the file!\n\n");
    } else {
        printf("File content cleared successfully!\n\n");
    }

    fclose(file);

    prompt();

}

void scroll_file(const char* file_name, int row_count){

    int row_index = 0;

    char row[MAX_TEXT_LENGTH];

    if (!does_file_exist(file_name)) {
        fprintf(stderr, "File does not exist!\n\n");
        prompt();
    }
    
    file = fopen(file_name, "r");

    while(fgets(row, MAX_TEXT_LENGTH, file) != NULL){
            
        if(row_index == row_count){
            row_index = 0;
            // getchar function is used to pause between pages
            getchar();
        }

        printf("%s", row);
        row_index++;

    }

    fclose(file);

    printf("\n");
    prompt();

}