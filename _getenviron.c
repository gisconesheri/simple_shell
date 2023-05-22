#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;
/**
 * _getenviron - gets the value of the environment variable passed in
 * @env_var: the environment variable
 * Returns: the value of env_var (what comes after the =)
 */

char *_getenviron(char *env_var)
{
	char *name = env_var;
	char *current_var;
	char variable[100];
	unsigned int i, j, k, value_present;
	char *name_value;

	i = j = k = value_present = 0;

	while (environ[i] != NULL)
	{
		current_var = environ[i];
		j = 0;

		while (current_var[j] != '=')
			j++;

		/*variable = malloc(sizeof(char) * j);*/
/*		if (variable == NULL)*/
/*			return (name_value);*/

		j = 0;

		while (current_var[j] != '=')
		{
			variable[j] = current_var[j];
			j++;
		}

		j = 0;
		while (name[j] != '\0')
		{
			if (name[j] == variable[j])
			{
				value_present = 1;
				j++;
				continue;
			}
			else
			{
				value_present = 0;
				break;
			}
		}

		k = 0;
		j++;
		if (value_present == 1)
		{
			name_value = malloc(sizeof(char) * strlen(current_var));
			if (name_value == NULL)
				return (name_value);

			while (current_var[j] != '\0')
			{
				name_value[k] = current_var[j];
				j++;
				k++;
			}
			name_value[k] = '\0';
			break;
		}

		i++;
	}
	return (name_value);
}
