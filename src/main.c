#include <stdio.h>
#include <stdlib.h>
#include "shell.h"

#define MAX_INPUT_SIZE 1024

int main() {
	    // Display welcome message
    printf("Welcome to MyShell! Type 'help' for the manual.\n");
    char input[MAX_INPUT_SIZE];
    char *args[MAX_INPUT_SIZE];

    while (1) {
        // Display prompt
        printf("%s$ ", getenv("PWD"));
        
        // Read user input
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break; // Exit loop on EOF or error
        }

        // Parse input into arguments
        parse_input(input, args);

        // Check for internal commands
        if (strcmp(args[0], "cd") == 0) {
            cd_command(args);
        } else if (strcmp(args[0], "clr") == 0) {
            clr_command();
        } else if (strcmp(args[0], "dir") == 0) {
            dir_command(args);
        } else if (strcmp(args[0], "environ") == 0) {
            environ_command();
        } else if (strcmp(args[0], "echo") == 0) {
            echo_command(args);
        } else if (strcmp(args[0], "help") == 0) {
            help_command();
        } else if (strcmp(args[0], "pause") == 0) {
            pause_command();
        } else if (strcmp(args[0], "quit") == 0) {
            quit_command();
            break; // Exit loop on quit command
        } else {
            // Execute external command
            execute_command(args);
        }
    }

    printf("Exiting myshell, GOODBYE!\n");

    return 0;
}
