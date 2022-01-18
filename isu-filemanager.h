#ifndef ISUFILEMANAGER_H
#define ISUFILEMANAGER_H

void prompt();
void split_run_command(char* command);
void create_file(char* file_name);
void delete_file(char* file_name);
void rename_file(char* old_file_name, char* new_file_name);
void copy_file(char* file_name, char* copied_file_name);
void move_file(char* file_name, char* destination);

#endif