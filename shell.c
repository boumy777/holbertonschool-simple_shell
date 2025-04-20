#include <stdio.h>
#include <stdlib.h>

/**
 * prompt_user_for_input - Affiche un prompt et lit l'entrée de l'utilisateur.
 * @input: Pointeur vers la chaîne d'entrée de l'utilisateur.
 */
void prompt_user_for_input(char **input)
{
	size_t len = 0;

	printf("Enter a command: ");
	if (getline(input, &len, stdin) == -1)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}
}

/**
 * process_input - Vérifie si l'entrée utilisateur est valide.
 * @input: La chaîne d'entrée de l'utilisateur.
 *
 * Return: 0 si l'entrée est valide, -1 sinon.
 */
int process_input(char *input)
{
	if (input == NULL || input[0] == '\n') /* Vérifie si l'entrée est vide */
	{
		fprintf(stderr, "Error: No input provided\n");
		return (-1);
	}
	return (0);
}

/**
 * execute_command - Exécute la commande donnée par l'utilisateur.
 * @input: La chaîne de commande.
 *
 * Return: 0 si la commande s'exécute avec succès, -1 sinon.
 */
int execute_command(char *input)
{
	if (system(input) == -1)
	{
		perror("Command failed");
		return (-1);
	}
	return (0);
}

/**
 * clean_up - Libère la mémoire allouée pour l'entrée.
 * @input: La chaîne d'entrée de l'utilisateur.
 */
void clean_up(char *input)
{
	free(input);
}

/**
 * main - Point d'entrée du programme.
 *
 * Return: 0 si tout s'exécute correctement, 1 sinon.
 */
int main(void)
{
	char *input = NULL;

	prompt_user_for_input(&input);

	if (process_input(input) == -1)
	{
		clean_up(input);
		return (1);
	}

	if (execute_command(input) == -1)
	{
		clean_up(input);
		return (1);
	}

	printf("Command executed successfully\n");
	clean_up(input);

	return (0);
}

