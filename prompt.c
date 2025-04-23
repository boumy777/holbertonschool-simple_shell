#include "utils.h"

/**
 * display_prompt - prints the shell prompt
 */
void display_prompt(void)
{
	write(1, "#cisfun$ ", 9);
}

/**
 * read_line - reads a line from stdin
 *
 * Return: pointer to the line (malloc'd), or NULL on EOF
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
		free(line);
		return (NULL);
	}

	/* Remove newline character */
	if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

