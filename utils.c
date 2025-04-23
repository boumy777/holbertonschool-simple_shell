#include <stdlib.h>
#include <string.h>

/**
 * trim_line - Supprime le saut de ligne
 * @line: la ligne lue
 * Return: ligne nettoyée
 */
char *trim_line(char *line)
{
	size_t len = strlen(line);

	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
	return (line);
}

