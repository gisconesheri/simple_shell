#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include "simple_shell.h"

/**
 * is_exit - checks if input entered is the string 'exit'
 * @argv_0: first argument for char **argv
 * Return: 1 if argv_0 is 'exit', o otherwise
 */
int is_exit(char *argv_0)
{
	char *exit_entry = "exit";
	int same = 0, i;

	for (i = 0; exit_entry[i] != '\0'; i++)
	{
		if (exit_entry[i] == argv_0[i])
		{
			same = 1;
			continue;
		}
		same = 0;
		break;
	}
	return (same);
}
/**
 * main - starts up the simple shell program
 * @ac: number of argumens supplied to main
 * @main_argv: array of strings passed to main
 * @envp: pointer to array of environment variables
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE otherwise
 */

int main(__attribute__((unused))int ac, char **main_argv, char **envp)
{
	char *command;
	size_t len = 10;
	ssize_t nlen = 0;
	int wstatus;
	pid_t child_process;
	char *argv[20];

	if (isatty(STDIN_FILENO))
		write(STDOUT_FILENO, "#cisfun$ ", 10);
	command = malloc(sizeof(char) * len);
	while ((nlen = getline(&command, &len, stdin)) != -1)
	{
		split_string(argv, command);
		if ((is_exit(argv[0]) == 1))
			exit(EXIT_SUCCESS);
		absolute_path(argv, envp);
		if (argv[0] != NULL)
		{
			child_process = fork();
			if (child_process == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			if (child_process == 0)
			{
				if ((execve(argv[0], argv, envp)) == -1)
					perror(main_argv[0]);
			}
			else
				wait(&wstatus);
		}
		else
			printf("%s: 1: %s: not found\n", main_argv[0], command);
		free(argv[0]);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 10);
	}
	return (EXIT_SUCCESS);
}
