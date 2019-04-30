#include "string.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{	

	// LINUX PATHS "~/games/packman.cpp+~alex/docs+~/study/Prog/lab4.c+/usr/bin/gcc\0";
	// WINDOWS PATHS "~\games\packman.cpp+~alex\docs+~\study\Prog\lab4.c+\usr\bin\gcc\0";

	char delim;
	char* username = (char *)malloc(sizeof(char) * MAX_USERNAME);
	char* dir = (char *)malloc(sizeof(char) * MAX_PATH);
	char* paths = (char *)malloc(sizeof(char) * MAX_PATH);
	char* os = (char *)malloc(sizeof(char) * MAX_OS);
	char* section_name = (char *)malloc(sizeof(char) * MAX_SECTION_NAME);

	input(username, paths, &delim, os, section_name);

	delete_n(username);
	delete_n(paths);
	delete_n(os);
	delete_n(section_name);

	slower(os);
	
	int os_type = choose_os(os);
	if (os_type == 7) {
		print_error(os_type);
		return -1;
	}

	if (os_type) {
		make_win_dir(username, dir, section_name);
	} else {
		make_unix_dir(username, dir);
	}

	int err_numb = check(username, dir, paths, delim, os_type, section_name);
	if (err_numb != 0) {
		print_error(err_numb);
		return -1;
	}
 
	process(dir, paths, delim, os_type);
	output(dir, paths, delim, os_type);

	free(username);
	free(dir);
	free(paths);
	free(os);
	free(section_name);

	return 0;
}