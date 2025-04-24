#include "shell.h"

/**
 * execute - Executes a command
 * @args: Array of arguments
 * @info: Pointer to the shell info struct
 *
 * Return: 1 to continue shell, 0 to exit
 */
int execute(char **args, info_t *info)
{
	int i;
	builtin_t builtins[] = {
		{"exit", shell_exit},
		{"env", shell_env},
		{NULL, NULL}
	};

	if (args[0] == NULL)
		return (1);

	for (i = 0; builtins[i].name; i++)
	{
		if (_strcmp(args[0], builtins[i].name) == 0)
			return (builtins[i].func(args, info));
	}

	return (execute_command(args, info));
}

/**
 * execute_command - Executes an external command
 * @args: Array of arguments
 * @info: Pointer to the shell info struct
 *
 * Return: 1 to continue shell
 */
int execute_command(char **args, info_t *info)
{
	pid_t pid;
	int status;
	char *cmd_path;

	cmd_path = get_cmd_path(args[0]);
	if (!cmd_path)
	{
		fprintf(stderr, "%s: %d: %s: not found\n",
				info->name, info->line_count, args[0]);
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(cmd_path, args, environ) == -1)
		{
			perror(info->name);
			free(cmd_path);
			exit(EXIT_FAILURE);
		}
	}
	else if (pid < 0)
	{
		perror(info->name);
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	free(cmd_path);
	return (1);
}

/**
 * build_path_candidate - Builds full path from directory and command
 * @dir: Directory path
 * @cmd: Command name
 *
 * Return: Full path or NULL
 */
char *build_path_candidate(char *dir, char *cmd)
{
	int cmd_len = _strlen(cmd);
	int dir_len = _strlen(dir);
	char *file_path = malloc(cmd_len + dir_len + 2);

	if (!file_path)
		return (NULL);

	_strcpy(file_path, dir);
	_strcat(file_path, "/");
	_strcat(file_path, cmd);

	return (file_path);
}

/**
 * get_cmd_path - Retrieves the full path of a command
 * @cmd: Command to find
 *
 * Return: Full path string or NULL if not found
 */
char *get_cmd_path(char *cmd)
{
	char *path, *path_copy, *path_token, *file_path;
	struct stat buffer;

	if (cmd[0] == '/' || cmd[0] == '.')
	{
		if (stat(cmd, &buffer) == 0)
			return (_strdup(cmd));
		return (NULL);
	}

	path = _getenv("PATH");
	if (!path)
		return (NULL);

	path_copy = _strdup(path);
	if (!path_copy)
		return (NULL);

	path_token = strtok(path_copy, ":");
	while (path_token)
	{
		file_path = build_path_candidate(path_token, cmd);
		if (!file_path)
		{
			free(path_copy);
			return (NULL);
		}
		if (stat(file_path, &buffer) == 0)
		{
			free(path_copy);
			return (file_path);
		}
		free(file_path);
		path_token = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}

