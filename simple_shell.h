#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

char **split_string(char **argv, char *getline_string);
char *_getenviron(char *name_value, char *env_var, char **envp);
char *path_exists(char *abs_path, char *path_value, char *command);
char *absolute_path(char **argv, char **envp);

#endif
