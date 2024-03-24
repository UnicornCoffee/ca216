#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

#define MAX_INPUT_SIZE 1024

int main(int argc, char *argv[]) {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_INPUT_SIZE];

    FILE *input_file = NULL;
    
    // Check if a command line argument is provided
    if (argc > 1) {
        // Open the specified file for reading
        input_file = fopen(argv[1], "r");
        if (input_file == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
    }
    printf("Welcome to MyShell! Type help for the manual!\n"); //Welcome message
    
    while (1) {
        // Check if input is from file or interactive mode
        if (input_file != NULL) {
            // Read command from file
            if (fgets(input, sizeof(input), input_file) == NULL) {
                // Exit loop when end-of-file is reached
                break;
            }
            // Print command being executed from file
            printf("Executing from file: %s", input);
        } else {
            // Prompt for input in interactive mode
            printf("%s$ ", getenv("PWD"));
            if (fgets(input, sizeof(input), stdin) == NULL) {
                break; // Exit loop on EOF or error
            }
        }

        // Parse input into arguments
        parse_input(input, args);

        // Check for input redirection symbol '<'
        int input_redirection_index = -1;
        for (int i = 0; args[i] != NULL; i++) {
            if (strcmp(args[i], "<") == 0) {
                input_redirection_index = i;
                break;
            }
        }

        // If input redirection symbol found, handle input redirection
        if (input_redirection_index != -1) {
            // Extract input filename
            char *input_filename = args[input_redirection_index + 1];
            
            // Redirect input stream
            handle_input_redirection(input_filename);
            
            // Remove input redirection symbols and filename from arguments
            args[input_redirection_index] = NULL;
            args[input_redirection_index + 1] = NULL;
        }

        // Check for internal commands (excluding input redirection symbol)
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

    // Close file if opened
    if (input_file != NULL) {
        fclose(input_file);
    }

    printf("Exiting MyShell.\n");

    return 0;
}
/*
DCU School of Computing
Assignment Submission
Student Name(s):    Isabelle O Keeffe
Student Number(s):    21731981
Programme:    BSc in Computer Science
Project Title:    myshell
Module code:    ca216
Lecturer:    Dr Graham Healy
Project Due Date:    24/03/2024


Declaration

I declare that this material, which I now submit for assessment, is entirely my own work and has not been taken from the work of others, save and to the extent that such work has been cited and acknowledged within the text of my work. I understand that plagiarism, collusion, and copying is a grave and serious offence in the university and accept the penalties that would be imposed should I engage in plagiarism, collusion, or copying. I have read and understood the Assignment Regulations set out in the module documentation. I have identified and included the source of all facts, ideas, opinions, viewpoints of others in the assignment references. Direct quotations from books, journal articles, internet sources, module text, or any other source whatsoever are acknowledged and the source cited are identified in the assignment references.

I have not copied or paraphrased an extract of any length from any source without identifying the source and using quotation marks as appropriate. Any images, audio recordings, video or other materials have likewise been originated and produced by me or are fully acknowledged and identified.

This assignment, or any part of it, has not been previously submitted by me or any other person for assessment on this or any other course of study. I have read and understood the referencing guidelines found at https://www.dcu.ie/library/citing-referencing and/or recommended in the assignment guidelines.

I understand that I may be required to discuss with the module lecturer/s the contents of this submission.

I/me/my incorporates we/us/our in the case of group work, which is signed by all of us.
*/
