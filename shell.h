#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

extern char **environ;

void signal_handler(int sig);
void execute_command(char *command);

#endif /* SHELL_H */

