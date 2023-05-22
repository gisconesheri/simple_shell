#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "simple_shell.h"

extern char **environ;
int _strlen(char *str)
{
	int len = 0;

	for (; str[len] != '\0'; len++)
		;

	return (len);
}
char **split_string(char *getline_string);
char *_getenviron(char *env_var);
char *path_exists(char *path_value, char *command);
char *absolute_path(char *argv_0);

int main(__attribute__((unused))int ac, char **main_argv)
{
	char *command = NULL;
	size_t len = 120;
	ssize_t nlen = 0;
	int wstatus;
	pid_t child_process;
	char **argv;

	command = malloc(sizeof(char) * len);

	write(STDOUT_FILENO, "#cisfun$ ", 10);
	while ((nlen = getline(&command, &len, stdin)) != -1)
	{

		argv = split_string(command);
		argv[0] = absolute_path(argv[0]);
		if (argv[0] != NULL)
		{
			child_process = fork();
			if (child_process == -1)
			{
				perror("fork");
				exit(-1);
			}
	
			if (child_process == 0)
			{
				if ((execve(argv[0], argv, environ)) == -1)
				{
					perror(main_argv[0]);
				}
			}
			else
			{
				wait(&wstatus);
			}
		}
		else
			continue;

		write(STDOUT_FILENO, "#cisfun$ ", 10);
		
	}
	return (0);
}
