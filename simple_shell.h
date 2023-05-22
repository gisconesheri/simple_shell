#ifndef SIMPLE_SHELL_H
#define SIMPLE_SHELL_H

char **split_string(char *getline_string);
char *_getenviron(char *env_var);
char *path_exists(char *path_value, char *command);
char *absolute_path(char *argv_0);

#endif
