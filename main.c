#include "shell.h"

/**
 * main - entry point for simple shell
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char **argv)
{
	char *line = NULL;
	char **args = NULL;
	int status = 1;
	info_t info = {0};

	/* Initialize shell info */
	info.name = argv[0];
	(void)argc;

	/* Set up signal handler */
	signal(SIGINT, handle_sigint);

	/* Main shell loop */
	while (status)
	{
		line = read_line(&info);
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		/* Skip empty lines */
		if (_strlen(line) == 0 || is_empty(line))
		{
			free(line);
			continue;
		}

		args = split_line(line);
		if (args == NULL)
		{
			free(line);
			continue;
		}

		status = execute(args, &info);

		free(line);
		free_args(args);
	}

	return (0);
}

/**
 * handle_sigint - handles SIGINT signal (Ctrl+C)
 * @sig: signal number
 *
 * Return: void
 */
void handle_sigint(int sig)
{
	(void)sig;
	printf("\n$ ");
	fflush(stdout);
}
