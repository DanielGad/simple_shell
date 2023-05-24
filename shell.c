#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

/**
 * display_prompt - Displays a prompt for the shell.
 */
void display_prompt(void)
{
	printf("YourShell$ ");
}

/**
 * read_input - Reads a line of input from the user.
 *
 * Return: The input string.
 */
char *read_input(void)
{
	char *input = malloc(MAX_COMMAND_LENGTH);

	if (input == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	if (fgets(input, MAX_COMMAND_LENGTH, stdin) == NULL)
	{
		free(input);
		return (NULL); /* Handle end of file (Ctrl+D) */
	}

	input[strcspn(input, "\n")] = '\0'; /* Remove trailing newline character */

	return (input);
}

/**
 * execute_command - Executes a command entered by the user.
 * @command: The command to be executed.
 */
void execute_command(char *command)
{
	pid_t child_pid;
	int status;

	if (strcmp(command, "exit") == 0)
	{
		printf("Exiting the shell...\n");
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(command, "env") == 0)
	{
		print_environment();
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (child_pid == 0)
		{
			/* Child process */
			if (execlp(command, command, NULL) == -1)
			{
				printf("Command not found or unable to execute: %s\n", command);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			/* Parent process */
			wait(&status);
		}
	}
}

/**
 * print_environment - Prints the environment variables.
 */
void print_environment(void)
{
	char **env = __environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
}

