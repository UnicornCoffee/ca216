#ifndef SHELL_H
#define SHELL_H

// Include necessary headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Function prototypes for internal commands
void cd_command(char *args[]);
void clr_command();
void dir_command(char *args[]);
void environ_command();
void echo_command(char *args[]);
void help_command();
void pause_command();
void quit_command();

// Function prototype for executing external commands
void execute_command(char *args[]);

// Function prototype for parsing user input
void parse_input(char *input, char *args[]);

#endif /* SHELL_H */
