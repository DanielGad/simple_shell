#include "shell.h"

void display_prompt(void)
{
	printf("shell> ");
	fflush(stdout);
}

void read_command(char *command)
{
	if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
	{
		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("fgets");
			exit(EXIT_FAILURE);
		}
	}
}

void execute_command(char *command)
{
	char *token;
	char *arguments[MAX_ARGUMENTS] = {NULL};
	int argCount = 0;
	pid_t pid;
	int status;

	command[strcspn(command, "\n")] = '\0';

	token = strtok(command, " ");
	while (token != NULL)
	{
		arguments[argCount++] = token;
		token = strtok(NULL, " ");
	}

	if (strcmp(arguments[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		if (execvp(arguments[0], arguments) == -1)
		{
			fprintf(stderr, "Command not found: %s\n", arguments[0]);
			exit(EXIT_FAILURE);
		}
	}

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("waitpid");
		exit(EXIT_FAILURE);
	}
}

