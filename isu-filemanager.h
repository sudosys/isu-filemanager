#ifndef ISUFILEMANAGER_H
#define ISUFILEMANAGER_H

void main_menu();
void split_run_command(char* command);
void create_file(char* file_name);
void delete_file(char* file_name);
void rename_file(char* old_file_name, char* new_file_name);
void copy_file(char* file_name, char* copied_file_name);

#endif