#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>

/* Constants */
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\r\n\a"

/* Global environment variable */
extern char **environ;

/**
 * struct info - shell info structure
 * @name: program name
 * @line_count: line count
 *
 * Description: Contains information about the shell's state
 */
typedef struct info
{
	char *name;
	int line_count;
} info_t;

/**
 * struct builtin - builtin command structure
 * @name: name of builtin command
 * @func: function pointer to builtin command
 *
 * Description: Structure for mapping builtin names to their functions
 */
typedef struct builtin
{
	char *name;
	int (*func)(char **, info_t *);
} builtin_t;

/* Main shell functions */
void handle_sigint(int sig);

/* Input reading and parsing functions */
char *read_line(info_t *info);
char **split_line(char *line);
int is_empty(char *line);
void free_args(char **args);

/* Command execution functions */
int execute(char **args, info_t *info);
int execute_command(char **args, info_t *info);
char *get_cmd_path(char *cmd);

/* Builtin functions */
int shell_exit(char **args, info_t *info);
int shell_env(char **args, info_t *info);

/* String helper functions */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *_strdup(const char *str);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);

/* Environment helper functions */
char *_getenv(const char *name);

#endif /* SHELL_H */
