#include "string.h"
#include <stdio.h>
#include <stdlib.h>

void input(char* username, char* paths, char* delim, char* os, char* section_name) 
{
	fputs("os [windows, linux]: ", stdout);
	fgets(os, MAX_OS, stdin);
	slower(os);
	if (scmp(os, "windows\n\0") == 0) {
		fputs("Section name: ", stdout);
		fgets(section_name, MAX_SECTION_NAME, stdin);
	}
	char temp[3];
    fputs("delim('+' or ' '): ", stdout);
    fgets(temp, 3, stdin);
    *delim = *temp;
    fputs("username: ", stdout);
    fgets(username, MAX_USERNAME, stdin);
    fputs("paths(max paths = 4): ", stdout);
    fgets(paths, MAX_PATH * 4 + 5, stdin);
}


int check(char* username, char* dir, char* paths, char delim, int os, char* section_name)
{
	/*Проверка корректности данных*/

	// Проверка разделителя
	if (delim != ' ' && delim != '+') {
		return 1;
	}

	int check_syn;
	if (os) {
		check_syn = check_windows(username, dir, paths, section_name);
		if (check_syn != 0) {
			return check_syn;
		}
	} else {
		check_syn = check_unix(username, paths);
		if (check_syn != 0) {
			return check_syn;
		}
	}

	char slash;
	if (os) {
		slash = '\\';
	} else {
		slash = '/';
	}
	// ПРОВЕРКА НА ДЛИНА ПУТИ > MAX_PATH ?
	char* result = (char *)malloc(sizeof(char) * MAX_PATH * 2);
	char* token = (char *)malloc(sizeof(char) * MAX_PATH);
	int index;
	while (slen(paths) > 0) {
		token = stok(paths, delim);
		index = slen(token) + 1;
		int i = 0;
		for (; dir[i] != '\0'; i++) {
			result[i] = dir[i];
		}
		for (int j = 0; token[j] != '\0'; j++, i++) {
			if (token[j] == '~' && token[j + 1] == slash) {
				i--;
				continue;
			} else if (token[j] == '~' && token[j + 1] != slash) {
				result[i] = slash;
				continue;
			}
			result[i] = token[j];
		}
		result[i] = '\0';
		if (i > MAX_PATH) {
			return 5;
		}
		paths = scpy(&paths[index]);
	}


	free(result);
	free(token);

	return 0;
}

int check_unix(char* username, char* paths)
{
	// ПРОВЕРКА НА ЗАПРЕЩЕННЫЕ СИМВОЛЫ
	char unix_forb_char[] = "\\\0";

	int check_syn = sspn(paths, unix_forb_char);
	if (check_syn == -1) {
		return 2;
	}

	check_syn = sspn(username, unix_forb_char);
	if (check_syn == -1) {
		return 3;
	}

	return 0;
}

int check_windows(char* username, char* dir, char* paths, char* section_name)
{
	// ПРОВЕРКА НА ЗАПРЕЩЕННЫЕ СИМВОЛЫ
	char win_forb_char[] = "/:*?«<>|";
	char win_dir_forb[] = "/*?«<>|";
	int check_syn = sspn(paths, win_forb_char);
	if (check_syn == -1) {
		return 2;
	}
	check_syn = sspn(username, win_forb_char);
	if (check_syn == -1) {
		return 3;
	}
	check_syn = sspn(dir, win_dir_forb);
	if (check_syn == -1) {
		return 4;
	}
	slower(section_name);
	for (int i = 0; section_name[i] != '\0'; i++) {
		if (section_name[i] < 'a' || section_name[i] > 'z') {
			return 6;
		}
	}
	return 0;
}

char* process(char* dir, char* paths, char delim, int os)
{
	char slash;
	if (os) {
		slash = '\\';
	} else {
		slash = '/';
	}
	/*Преобразование к абсолютным путям*/
	char* result = (char *)malloc(sizeof(char) * MAX_PATH * 4 + 4);
	char* token = (char *)malloc(sizeof(char) * MAX_PATH);
	int index;
	int i = 0;
	while (slen(paths) > 0) {
		token = stok(paths, delim);
		index = slen(token) + 1;
		if (i > 0) {
			result[i] = delim;
			i++;
		}
		//printf("%d\n", index);
		if (token[0] == '~' && token[1] == slash) {
			for (int j = 0; dir[j] != '\0'; i++, j++) {
				result[i] = dir[j];
			}
			for (int j = 1; token[j] != '\0'; i++, j++) {
				result[i] = token[j];
			}
			paths = scpy(&paths[index]);
			continue;
		}
		for (int j = 0; token[j] != '\0'; j++, i++) {
			result[i] = token[j];
		}
		paths = scpy(&paths[index]);
	}
	free(token);
	return result;
}

void output(char* dir, char* paths, char delim, int os)
{
	char* result = (char *)malloc(sizeof(char) * MAX_PATH * 4 + 4);
	result = process(dir, paths, delim, os);
	printf("%s\n", result);
	free(result);
}

int slen(char* str)
{
	/*Длина строки*/
	int i;
	for (i = 0; str[i] != '\0'; i++) {}
	return i;
}

char* stok(char* str, char delim)
{
	/*Разбиение строки на элементы-токены*/
	char* token = (char *)malloc(sizeof(char) * MAX_PATH);
	if (token == NULL || str == NULL) {
		return NULL;
	}
	for (int i = 0;; i++) {
		if (str[i] == delim || str[i] == '\0') {
			token[i] = '\0';
			return token;
		}
		token[i] = str[i];
	}
}

int sspn(char* str, char* forb_char)
{
	/*Проверка допустимости используемых символов*/
	for (int i = 0; str[i] != '\0'; i++) {
		for (int j = 0; j < slen(forb_char) + 1; j++) {
			if (str[i] == forb_char[j]) {
				return -1;
			}
		}
	}
	return 0;
}

int scmp(char *cs, char *ct) {
    char c1, c2;

    while (1) {
        c1 = *cs++;
        c2 = *ct++;
        if (c1 != c2) {
            return c1 < c2 ? -1 : 1;
        }
        if (!c1) {
            break;
        }
    }
    return 0;
}

char* scpy(char* str)
{
	/*Копирование str1 в str2*/
	char* strCopy = (char *)malloc(sizeof(char) * MAX_PATH);

	if (str == NULL || strCopy == NULL) {
		return NULL;
	}

	int i;
	for (i = 0; str[i] != '\0'; i++) {
		strCopy[i] = str[i];
	}
	strCopy[i] = '\0';

	return strCopy;
}

int choose_os(char* os)
{
	if (scmp(os, "windows\0") == 0) {
		return 1;
	} else if (scmp(os, "linux\0") == 0) {
		return 0;
	}
	return 7;
}

void slower(char* str) 
{
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = str[i] - 'A' + 'a';
		}
	}
}

int delete_n(char* str)
{
	int index_n = slen(str) - 1;
	if (str[index_n] != '\n') {
		return 1;
	}
	str[index_n] = '\0';
	return 0;
}

void make_win_dir(char* username, char* win_dir, char* section_name)
{
	char* win_home = ":\\Users\\\0";
	int i;
	for (i = 0; section_name[i] != '\0'; i++) {
		win_dir[i] = section_name[i];
	}
	for (int j = 0; win_home[j] != '\0'; i++, j++) {
		win_dir[i] = win_home[j];
	}
	for (int j = 0; username[j] != '\0'; i++, j++) {
		win_dir[i] = username[j];
	}
	win_dir[i] = '\0';
}

void make_unix_dir(char* username, char* unix_dir)
{
	char unix_home[] = "/home/\0";
	int i;
	for (i = 0; i < 6; i++) {
		unix_dir[i] = unix_home[i];
	}
	for (int j = 0; j < slen(username); i++, j++) {
		unix_dir[i] = username[j];
	}
	unix_dir[i] = '\0';
}

void print_error(int error_numb)
{
	switch(error_numb) {
		case 1:
			printf("DELIM PROBLEMO\n");
			break;
		case 2:
			printf("PATH ERROR\n");
			break;
		case 3:
			printf("USERNAME ERROR");
			break;
		case 4:
			printf("WIN DIR ERROR\n");
			break;
		case 5:
			printf("MAX_PATH_ERROR\n");
			break;
		case 6:
			printf("WIN SECTION NAME ERROR\n");
			break;
		case 7:
			printf("OS ERROR\n");
			break;
	}
}
