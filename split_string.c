#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * split_string - split a string from getline function into an array
 * to be passed on to the argv portion of execve
 * @getline_string: string gotten from the stdin by getline function
 * Return: an array of string pointers
 */

char **split_string(char *getline_string)
{
	char **execv_argv, **new_argv;
	char *program_name, *last_string;
	int len = 1, k = 0, ls_len = 0;

	program_name = strtok(getline_string, " ");

	execv_argv = malloc(sizeof(program_name) * len);
	if (execv_argv == NULL)
		exit(-1);

	execv_argv[0] = program_name;
	
	while (program_name != NULL)
	{
		len++;
		program_name = strtok(NULL, " ");
		new_argv = malloc(sizeof(program_name) * len + 1);
		if (new_argv == NULL)
			exit(-1);
		for(k = 0; k < len - 1; k++)
		{
			new_argv[k] = execv_argv[k];
		}
		new_argv[k] = program_name;
		if (program_name == NULL)
		{
			last_string = new_argv[k - 1];
			ls_len = strlen(last_string);
			last_string[ls_len - 1] = '\0';
			new_argv[k - 1] = last_string;
		}

		execv_argv = new_argv;
	}

	return (execv_argv);
}
