#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

/**
 * main - Entry point
 * Description: a main function
 *
 * Return: 0 success.
 */

int main(void)
{
	char *input;

	while (1)
	{
		display_prompt();
		input = read_input();

		if (input == NULL)
		{
			printf("\n");
			break; /* Handle end of file (Ctrl+D) */
		}

		execute_command(input);

		free(input); /* Free dynamically allocated input */
	}

	return (0);
}

