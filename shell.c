#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
void display_prompt(void)
{
printf(":) ");
}
char *read_command(void)
{
char *user_input = malloc(sizeof(char) * 100);
if (user_input == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}
if (scanf(" %[^\n]", user_input) != 1)
{
printf(":( ");
perror("scanf");
free(user_input);
exit(EXIT_FAILURE);
}
return (user_input);
}
char **parse_command(char *command)
{
char **args = malloc(sizeof(char *) * 100);
if (args == NULL)
{
perror("malloc");
exit(EXIT_FAILURE);
}
char *token = strtok(command, " ");
int i = 0;
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
int main(int argc, char *argv[])
{
while (1)
{
display_prompt();
char *user_input = read_command();
if (user_input == NULL)
break;
char **args = parse_command(user_input);
if (args == NULL)
{
free(user_input);
continue;
}
execute_command(args);
free(user_input);
for (int i = 0; args[i] != NULL; i++)
{
free(args[i]);
}
free(args);
}
return (0);
}
