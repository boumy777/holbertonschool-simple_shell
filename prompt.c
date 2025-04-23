#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * display_prompt - Affiche le prompt ($ )
 */
void display_prompt(void)
{
	write(1, "$ ", 2);
}

/**
 * read_line - Lit une ligne de l'utilisateur
 *
 * Return: la ligne lue ou NULL si une erreur est rencontrée
 */
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;

	if (getline(&line, &len, stdin) == -1)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

