#pragma once

#define MAX_PATH 260
#define MAX_USERNAME 255
#define MAX_OS 25
#define MAX_SECTION_NAME 4

void output(char* dir, char* path, char delim, int os);
void print_error(int error_numb);
void make_unix_dir(char* username, char* unix_dir);
void make_win_dir(char* username, char* win_dir, char* section_name);
int delete_n(char* str);
int check_unix(char* username, char* path);
int check_windows(char* username, char* dir, char* path, char* section_name);
void slower(char* str);
int choose_os(char* os);
void input(char* username, char* paths, char* delim, char* os, char* section_name);
int check(char* username, char* dir, char* path, char delim, int os, char* section_name);
char* stok(char* str, char delim);
char* scpy(char* str);
int slen(char* str);
int sspn(char* str, char* forb_char);
int scmp(char *cs, char *ct);
char* process(char* dir, char* path, char delim, int os);
