#include <sys/wait.h>
#include "main.h"

/**
 * display_prompt - Affiche le prompt du shell
 */
void display_prompt(void)
{
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}

/**
 * read_line - Lit une ligne depuis l'entrée standard
 * Return: ligne lue (malloc), NULL si Ctrl+D
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

	if (line[nread - 1] == '\n')
		line[nread - 1] = '\0';

	return (line);
}

/**
 * execute_command - Exécute une commande simple avec execve
 * @cmd: commande (chemin absolu)
 */
void execute_command(char *cmd)
{
	pid_t pid = fork();
	char *argv[] = {cmd, NULL};

	if (pid == -1)
	{
		perror("fork");
		return;
	}
	if (pid == 0)
	{
		if (execve(cmd, argv, environ) == -1)
		{
			perror("./shell");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(NULL);
	}
}

/**
 * main - Point d'entrée du shell
 * Return: 0
 */
int main(void)
{
	char *line;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			display_prompt();

		line = read_line();
		if (line == NULL)
		{
			if (isatty(STDIN_FILENO))
				write(STDOUT_FILENO, "\n", 1);
			break;
		}
		execute_command(line);
		free(line);
	}
	return (0);
}

