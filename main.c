#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
/**
 * main - Entry point for the simple shell
 *
 * Return: Always 0 (Success)
 */

int main(void)
{
	char *line;

	while (1)
	{
		display_prompt();
		line = read_line();
		if (!line)
		{
			printf("\n");
			break;
		}
		printf(">> %s", line);
		free(line);
	}
	return (0);
}

