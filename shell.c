#include "shell.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>

/**
 * signal_handler - Handles Ctrl+C (SIGINT) input.
 * @sig: signal number.
 *
 * This function is called when SIGINT is received, and it will print a
 * new prompt after a Ctrl+C is pressed.
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
 *
 * This function creates a child process using fork(), and the child process
 * attempts to execute the given command using execve(). If execve fails, it
 * prints an error message and exits. The parent process waits for the child
 * process to finish.
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

	if (pid == 0)  /* Child process */
	{
		argv[0] = command;
		argv[1] = NULL;

		/* Check if the command exists before executing */
		if (access(command, F_OK) == -1)
		{
			perror(command);
			exit(EXIT_FAILURE);
		}

		if (execve(command, argv, environ) == -1)
		{
			perror(command);
			exit(EXIT_FAILURE);
		}
	}
	else  /* Parent process */
	{
		wait(NULL);
	}
}

/**
 * get_input - Reads the user input and returns it.
 *
 * Return: The input string.
 */
char *get_input(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t line_size;

	line_size = getline(&line, &len, stdin);

	if (line_size == -1) /* Handle EOF (Ctrl+D) */
	{
		write(STDOUT_FILENO, "\n", 1);
		free(line);
		exit(EXIT_SUCCESS);
	}

	/* Remove newline character from the input */
	line[strcspn(line, "\n")] = 0;

	return line;
}

/**
 * process_input - Processes the input line to check for empty input.
 * @line: The line to process.
 */
void process_input(char *line)
{
	if (strlen(line) > 0) /* Avoid empty input */
	{
		execute_command(line);
	}
}

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void)
{
	char *prompt = "#cisfun$ ";
	write(STDOUT_FILENO, prompt, strlen(prompt));
}

/**
 * main - Entry point of the simple shell program.
 *
 * This function displays the prompt, waits for user input, and executes
 * the command. It handles the end-of-file (Ctrl+D) and exits gracefully
 * when detected.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;

	/* Set the signal handler for SIGINT (Ctrl+C) */
	signal(SIGINT, signal_handler);

	while (1)
	{
		display_prompt();
		line = get_input();
		process_input(line);
		free(line); /* Free the allocated memory */
	}

	return (0);
}

