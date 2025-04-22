#ifndef MAIN_H
#define MAIN_H

#include <unistd.h>

extern char **environ;

char *read_command(void);
void execute_command(char *cmd);

#endif /* MAIN_H */

