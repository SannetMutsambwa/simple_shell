#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
/* Global Variables */
extern char **environ;
/* Function Prototypes */
void printAlphabet(void);
void display_prompt(void);
char *read_command(void);
char **parse_command(char *command);
void execute_command(char **args);
int _strcmp(const char *s1, const char *s2);
char *_strcat(char *dest, const char *src);
int _strlen(const char *s);
void free_array(char **array);
char *_strdup(const char *str);
int _putchar(char c);
void print_env(void);
void handle_exit(void);
#endif /* MAIN_H */
