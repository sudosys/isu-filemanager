#ifndef ISUFILEMANAGER_H
#define ISUFILEMANAGER_H

void prompt();
void run_command(char* command);
int does_file_exist(const char* file_name);
void create_file(const char* file_name);
void delete_file(const char* file_name);
void rename_file(const char* old_file_name, const char* new_file_name);
void copy_file(const char* file_name, const char* copied_file_name);
void move_file(const char* file_name, const char* destination);
void append_file(const char* file_name);
void insert_file(const char* file_name, int insertion_pos);
void clear_file(const char* file_name);
void scroll_file(const char* file_name, int row_count);

#endif