#include "shell.h"

int main(void)
{
	char command[MAX_COMMAND_LENGTH];

while (1)
	{
		display_prompt();
		read_command(command);

		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}

		if (strcmp(command, "exit") == 0)
		{
			exit(EXIT_SUCCESS);
		}
		else if (strcmp(command, "env") == 0)
		{
			char **env = __environ;

while (*env)
{
				printf("%s\n", *env);
				env++;
			}
		}
		else
		{
			execute_command(command);
		}
	}

	return (0);
}

