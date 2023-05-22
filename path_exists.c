#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/**
 * path_exists - builds and absolute path name and
 *  checks if the path for command is valid/exists
 * @path_value: the PATH value from envrion
 * @command: the command supplied by user
 * Return: the absolute file path containing the command
 * NULL if no path exists
 */

char *path_exists(char *path_value, char *command)
{
	int len, i, j, path_len;
	char *temp_path_is, *current_file, *current_path;
	char *temp_file_path = NULL;
	struct stat file_info;
	char *temp_path = NULL;
	char *saveptr = NULL;

	i = j = len = path_len = 0;

	/*create new pointer so as that strtok doesnt intefer with the path*/
		temp_path_is = malloc(sizeof(char) * strlen(path_value));
		for (path_len = 0; path_value[path_len]; path_len++)
			temp_path_is[path_len] = path_value[path_len];


		temp_path = temp_path_is;

/*get the first path in PATH out of the path string using strtok_r*/
		current_path = strtok_r(temp_path, ":", &saveptr);
		current_file = command;

		/*iterate thrhough all paths in the the PATH*/
		while (current_path != NULL)
		{
			/*create a string to hold the full path name*/
			/*DO NOT intefere with current_path*/
			len = strlen(current_path) + strlen(current_file);
			temp_file_path = malloc(sizeof(char) * (len + 2));

			i = 0;
			while (current_path[i] != '\0')
			{
				temp_file_path[i] = current_path[i];
				i++;
			}
			temp_file_path[i] = '/';

			/*add the argument supplied to the semi-finished path name*/
			j = 0;
			i++;
			while (current_file[j] != '\0')
			{
				temp_file_path[i] = current_file[j];
				i++;
				j++;
			}
			temp_file_path[i] = '\0';

/*search if the full path name can be found in the system using STAT()*/
			if ((stat(temp_file_path, &file_info)) == 0)
			{

				return (temp_file_path);
			}
/*Move to the next path in PATH, strtok needs NULL pointer after first call*/
			current_path = strtok_r(NULL, ":", &saveptr);
			len = 0;
		}
	temp_file_path = NULL;
	return (temp_file_path);
}
