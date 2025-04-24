#include "shell.h"

/**
 * signal_handler - Handles signals received by the shell
 * @signum: Signal number received
 *
 * Return: void
 */
void signal_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n$ ", 3);
		fflush(stdout);
	}
}

/**
 * execute_command - Executes a given command
 * @command: Command to execute
 *
 * Return: Exit status of the command
 */
int execute_command(char *command)
{
	int status;

	if (!command)
		return (1);

	status = system(command);
	return (status);
}

/**
 * parse_input - Parses command line input
 * @input: Raw command line
 * @args: Array to store arguments
 *
 * Return: Number of arguments
 */
int parse_input(char *input, char **args)
{
	int count = 0;
	char *token;

	token = strtok(input, " \t\n");
	while (token != NULL && count < 64)
	{
		args[count++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[count] = NULL;

	return (count);
}

/**
 * display_prompt - Displays shell prompt
 *
 * Return: void
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "$ ", 2);
}

/**
 * main - Entry point of the program
 *
 * Return: 0 on success
 */
int main(void)
{
	signal(SIGINT, signal_handler);

	while (1)
	{
		display_prompt();
	}

	return (0);
}
