#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

extern char **environ;

void display_prompt(void);
char *read_line(void);
void execute_command(char *cmd);

#endif

