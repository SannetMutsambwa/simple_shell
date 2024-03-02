#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#define MAX_ARGS 100
void display_prompt(void);
char *read_command(void);
char **parse_command(char *user_input);
char *search_path(char *command);
void execute_command(char **args, char *argv_0);
/**
* main - Entry point of the simple shell program.
* @argc: The number of arguments passed to the program.
* @argv: An array of strings containing the arguments.
* Return: Always 0.
*/

int main(int argc, char **argv)
{
char *user_input;
char **args;
char *program_name = argc > 0 ? argv[0] : "hsh";
if (argc == 1)
{
while (1)
{
display_prompt();
user_input = read_command();
args = parse_command(user_input);
if (args[0] == NULL)
{
free(user_input);
free(args);
continue;
}
if (strcmp(args[0], "exit") == 0)
{
free(user_input);
free(args);
break;
}
execute_command(args, program_name);
free(user_input);
free(args);
}
}
else if (argc == 2)
{
fprintf(stderr, "Usage: %s\n", program_name);
exit(EXIT_FAILURE);
}
else
{
fprintf(stderr, "Usage: %s\n", program_name);
exit(EXIT_FAILURE);
}
return (0);
}
/**
* display_prompt - Displays the shell prompt.
*/
void display_prompt(void)
{
if (isatty(STDIN_FILENO))
{
printf("($) ");
fflush(stdout);
}
}
/**
* read_command - Reads a command from standard input
* Return: A pointer to the user input.
*/
char *read_command(void)
{
char *user_input = NULL;
size_t bufsize = 0;
if (isatty(STDIN_FILENO))
{
printf(" ");
}
if (getline(&user_input, &bufsize, stdin) == -1)
{
free(user_input);
if (isatty(STDIN_FILENO))
printf("\n");
exit(EXIT_SUCCESS);
}
return (user_input);
}
/**
* parse_command - Parses a command string into an array of arguments.
* @user_input: The command string to parse.
* Return: An array of strings containing the arguments.
*/
char **parse_command(char *user_input)
{
char *token;
int i = 0;
char **args = malloc(MAX_ARGS * sizeof(char *));
if (!args)
{
fprintf(stderr, "Memory allocation failed\n");
exit(EXIT_FAILURE);
}
token = strtok(user_input, " \t\n");
while (token != NULL)
{
args[i++] = token;
token = strtok(NULL, " \t\n");
}
args[i] = NULL;
return (args);
}
/**
* search_path - Searches for the path of a command..
* @command: The command to search for.
* Return: The full path of the command if found, otherwise NULL.
*/
char *search_path(char *command)
{
char *path = getenv("PATH");
char *path_copy = strdup(path);
char *token = strtok(path_copy, ":");
while (token != NULL)
{
char *path_to_exec = malloc(strlen(token) + strlen(command) + 2);
strcpy(path_to_exec, token);
strcat(path_to_exec, "/");
strcat(path_to_exec, command);
if (access(path_to_exec, X_OK) == 0)
{
free(path_copy);
return (path_to_exec);
}
free(path_to_exec);
token = strtok(NULL, ":");
}
free(path_copy);
return (NULL);
}
/**
* execute_command - Executes a command with given arguments.
* @args: An array of strings with the command and its arguments.
* @argv_0: The name of the program.
*/
void execute_command(char **args, char *argv_0)
{
pid_t pid;
char *full_path;
full_path = search_path(args[0]);
pid = fork();
if (full_path == NULL)
{
fprintf(stderr, "%s: 1: %s: not found\n", argv_0, args[0]);
return;
}
if (pid < 0)
{
fprintf(stderr, "%s: unable to fork\n", argv_0);
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
if (execvp(full_path, args) == -1)
{
fprintf(stderr, "%s: 1: %s: command not found\n", argv_0, args[0]);
exit(EXIT_FAILURE);
}
}
else
{
int status;
waitpid(pid, &status, 0);
}
free(full_path);
}
