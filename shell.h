#ifndef SHELL_H
#define SHELL_H

#define MAX_COMMAND_LENGTH 100

void display_prompt(void);
char *read_input();
void execute_command(char *command);
void print_environment(void);

#endif


