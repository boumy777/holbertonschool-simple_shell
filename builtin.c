#include "shell.h"

/**
 * shell_exit - builtin command: exit
 * @args: arguments
 * @info: shell info struct
 *
 * Return: 0 to exit shell
 */
int shell_exit(char **args, info_t *info)
{
	(void)args;
	(void)info;
	return (0);
}

/**
 * shell_env - builtin command: env
 * @args: arguments
 * @info: shell info struct
 *
 * Return: 1 to continue executing
 */
int shell_env(char **args, info_t *info)
{
	int i = 0;

	(void)args;
	(void)info;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}

	return (1);
}
