#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
/**
* display_prompt - Displays the prompt for user input.
*/
void display_prompt(void)
{
if (isatty(STDIN_FILENO))
{
printf(":) ");
fflush(stdout);
}
}
/**
* read_command - Reads a command entered by the user.
* Return: The command entered by the user.
*/
char *read_command(void)
{
char *user_input = malloc(sizeof(char) * 100);
if (user_input == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}
if (isatty(STDIN_FILENO))
{
printf(":) ");
fflush(stdout);
}
if (fgets(user_input, 100, stdin) == NULL)
{
if (feof(stdin))
{
free(user_input);
return (NULL);
}
perror("fgets");
free(user_input);
exit(EXIT_FAILURE);
}
user_input[strcspn(user_input, "\n")] = 0;
return (user_input);
}
/**
* parse_command - Parses the command string into arguments.
* @command: The command string to parse.
* Return: An array of arguments.
*/
char **parse_command(char *command)
{
int i = 0;
char *token;
char **args = malloc(sizeof(char *) * 100);
if (args == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}
token = strtok(command, " ");
while (token != NULL)
{
args[i] = strdup(token);
if (args[i] == NULL)
{
perror("strdup");
exit(EXIT_FAILURE);
}
token = strtok(NULL, " ");
i++;
}
args[i] = NULL;
return (args);
}
/**
* execute_command - Executes the given command.
* @args: The array of arguments representing the command.
*/
void execute_command(char **args)
{
pid_t pid = fork();
if (pid < 0)
{
perror("fork");
exit(EXIT_FAILURE);
}
else if (pid == 0)
{
if (execvp(args[0], args) == -1)
{
perror("execvp");
exit(EXIT_FAILURE);
}
}
else
{
int status;
waitpid(pid, &status, 0);
}
}
/**
* main - Entry point of the program.
* Return: Always 0.
*/
int main(void)
{
char *user_input;
char **args;
int i;
while (1)
{
display_prompt();
user_input = read_command();
if (user_input == NULL)
{
printf("\n");
break;
}
if (strlen(user_input) == 0)
{
free(user_input);
continue;
}
args = parse_command(user_input);
if (args == NULL)
{
free(user_input);
continue;
}
execute_command(args);
free(user_input);
for (i = 0; args[i] != NULL; i++)
{
free(args[i]);
}
free(args);
}
return (0);
}
