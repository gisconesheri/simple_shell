#include <stdio.h>
#include "simple_shell.h"

char *_getenviron(char *env_var);
char *path_exists(char *path_value, char *command);
/**
 * absolute_path - generates an absolute file path for command using
 * PATH variable
 * @argv_0: command which to get the file path
 * Return: the absolute filepath or NULL if not found
 */

char *absolute_path(char *argv_0)
{
	char *supplied_name;
	char *path_value;
	char *abs_path;

	supplied_name = argv_0;

	if (supplied_name[0] == '/')
	{
		return (argv_0);
	}

	path_value = _getenviron("PATH");

	abs_path = path_exists(path_value, supplied_name);

	return (abs_path);
}
