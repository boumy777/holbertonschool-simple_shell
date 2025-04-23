#include "utils.h"

/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0
 */
int main(void)
{
	char *line = NULL;

	while (1)
	{
		display_prompt();
		line = read_line();
		if (line == NULL)
		{
			write(1, "\n", 1);
			break;
		}
		execute_command(line);
		free(line);
	}

	return (0);
}

