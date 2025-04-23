#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

void display_prompt(void);
char *read_line(void);
void execute_command(char *cmd);

#endif

