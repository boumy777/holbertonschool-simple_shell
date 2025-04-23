#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "main.h"

/**
 * execute_command - Exécute une commande simple sans arguments
 * @cmd: chemin de la commande à exécuter
 *
 * Return: rien
 */
void execute_command(char *cmd)
{
	char *argv[2];

	argv[0] = cmd;
	argv[1] = NULL;

	if (execve(cmd, argv, environ) == -1)
	{
		perror("Error");
	}
}

