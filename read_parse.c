#include "shell.h"

/**
 * read_line - reads a line from stdin
 * @info: shell info struct
 *
 * Return: pointer to the line read
 */
char *read_line(info_t *info)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t chars_read;

	/* Display prompt if in interactive mode */
	if (isatty(STDIN_FILENO))
		printf("$ ");

	chars_read = getline(&line, &bufsize, stdin);

	if (chars_read == -1)
	{
		/* Handle EOF or error */
		if (line)
			free(line);
		return (NULL);
	}

	/* Remove newline character */
	if (line[chars_read - 1] == '\n')
		line[chars_read - 1] = '\0';

	info->line_count++;
	return (line);
}

/**
 * split_line - splits a line into tokens
 * @line: the line to split
 *
 * Return: array of tokens
 */
char **split_line(char *line)
{
	int bufsize = TOK_BUFSIZE, position = 0;
	char **tokens = malloc(bufsize * sizeof(char *));
	char *token;

	if (!tokens)
	{
		perror("malloc");
		return (NULL);
	}

	token = strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		tokens[position] = _strdup(token);
		position++;

		if (position >= bufsize)
		{
			bufsize += TOK_BUFSIZE;
			tokens = realloc(tokens, bufsize * sizeof(char *));
			if (!tokens)
			{
				perror("realloc");
				return (NULL);
			}
		}

		token = strtok(NULL, TOK_DELIM);
	}
	tokens[position] = NULL;
	return (tokens);
}

/**
 * is_empty - checks if a line is empty or only whitespace
 * @line: line to check
 *
 * Return: 1 if empty, 0 otherwise
 */
int is_empty(char *line)
{
	int i;

	for (i = 0; line[i]; i++)
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
	}

	return (1);
}

/**
 * free_args - frees array of strings
 * @args: array of strings
 *
 * Return: void
 */
void free_args(char **args)
{
	int i;

	if (!args)
		return;

	for (i = 0; args[i]; i++)
		free(args[i]);

	free(args);
}
