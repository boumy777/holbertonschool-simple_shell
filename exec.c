#include "utils.h"

/**
 * execute_command - uses execve to run the input command
 * @cmd: the command to run (full path)
 */
void execute_command(char *cmd)
{
	char *argv[] = {cmd, NULL};

	if (execve(cmd, argv, environ) == -1)
	{
		perror("./shell");
	}
}

