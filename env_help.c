#include "shell.h"

/**
 * _getenv - gets an environment variable
 * @name: name of the variable
 *
 * Return: pointer to the variable value or NULL
 */
char *_getenv(const char *name)
{
	int i = 0, j;
	int name_len;

	if (!name)
		return (NULL);

	name_len = _strlen((char *)name);

	while (environ[i])
	{
		j = 0;
		while (environ[i][j] && j < name_len && environ[i][j] == name[j])
			j++;

		if (j == name_len && environ[i][j] == '=')
			return (environ[i] + j + 1);
		i++;
	}

	return (NULL);
}
