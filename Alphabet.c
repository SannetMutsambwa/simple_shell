#include "shell.h"
#include <stdio.h>
/**
* printAlphabet - Prints the alphabet 'a' to 'z'
*/
void printAlphabet(void)
{
char alphabet;
for (alphabet = 'a'; alphabet <= 'z'; alphabet++)
{
printf("%c ", alphabet);
}
printf("\n");
}
/**
* main - Entry point of the program.
* while loop will prompt the user until a valid alphabet is entered.
* Return: Always 0 (sucess)
*/
int main(void)
{
printAlphabet();
char input;
while (1)
{
printf("Enter an alphabet: ");
scanf(" %c", &input);
input = (input >= 'A' && input <= 'Z') ? input + ('a' - 'A') : input;
if (input >= 'a' && input <= 'z')
{
printf("The number of the alphabet '%c' is: %d\n", input, input - 'a' + 1);
break;
}
else
{
printf("Invalid input!!\n");
}
}
}
