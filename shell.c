#include "shell.h"

/**
 * signal_handler - Handles Ctrl+C (SIGINT) input.
 * @sig: signal number.
 */
void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n#cisfun$ ", 10);
	}
}

/**
 * execute_command - Forks and executes a command using execve.
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	pid_t pid = fork();
	char *argv[2];

	if (pid == -1)
	{
		perror("fork");
		return;
	}

	if (pid == 0)
	{
		argv[0] = command;
		argv[1] = NULL;

		if (execve(command, argv, environ) == -1)
		{
			perror(command);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}

/**
 * main - Entry point of the simple shell program.
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t line_size;
	char *prompt = "#cisfun$ ";

	signal(SIGINT, signal_handler);

	while (1)
	{
		write(STDOUT_FILENO, prompt, strlen(prompt));
		line_size = getline(&line, &len, stdin);

		if (line_size == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			free(line);
			exit(EXIT_SUCCESS);
		}

		line[strcspn(line, "\n")] = 0;

		if (strlen(line) > 0)
		{
			execute_command(line);
		}
	}

	free(line);
	return (0);
}

