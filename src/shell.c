#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "shell.h"

/*
    This code implements a set of basic shell commands:

    - cd_command: Changes the directory and updates the PWD environment variable if an argument is provided, otherwise prints the current directory.
    - clr_command: Clears the screen using ANSI escape sequences.
    - dir_command: Lists the contents of a directory. If no argument is provided, it defaults to the current directory.
    - environ_command: Lists all environment variables.
    - echo_command: Prints arguments to the console.
    - help_command: Displays a manual file by piping its content through the 'more' command.
    - pause_command: Pauses execution until the Enter key is pressed.
    - quit_command: Exits the shell gracefully.
*/


// Change directory command
void cd_command(char *args[]) {
    if (args[1] == NULL) {
        // No argument provided, print current directory
        printf("%s\n", getenv("PWD"));
    } else {
        // Change directory and update PWD environment variable
        if (chdir(args[1]) != 0) {
            perror("cd");
        } else {
            setenv("PWD", args[1], 1);
        }
    }
}

// Clear screen command
void clr_command() {
    printf("\033[2J\033[H"); // ANSI escape sequence to clear screen
}

// List directory contents command
void dir_command(char *args[]) {
    char *dir_path = args[1] ? args[1] : "."; // Default to current directory if no argument provided
    DIR *dir = opendir(dir_path);
    if (dir == NULL) {
        perror("dir");
        return;
    }
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }
    closedir(dir);
}

// List environment variables command
void environ_command() {
    extern char **environ;
    for (char **env = environ; *env != NULL; env++) {
        printf("%s\n", *env);
    }
}

// Echo command
void echo_command(char *args[]) {
    for (int i = 1; args[i] != NULL; i++) {
        printf("%s ", args[i]);
    }
    printf("\n");
}


void help_command() {
    // Open the manual file for reading
    FILE *manual_file = fopen("manual/readme", "r");
    if (manual_file == NULL) {
        perror("fopen");
        return;
    }

    // Execute the more command as a child process
    FILE *more_process = popen("more", "w");
    if (more_process == NULL) {
        perror("popen");
        fclose(manual_file);
        return;
    }

    // Read from the manual file and write to the more process
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), manual_file) != NULL) {
        fputs(buffer, more_process);
    }

    // Close file pointers
    fclose(manual_file);
    pclose(more_process);
}

// Pause command
void pause_command() {
    printf("Press Enter to continue\n");
    while (getchar() != '\n');
}

// Quit command
void quit_command() {
    printf("Exiting shell. Goodbye! \n");
    exit(EXIT_SUCCESS);
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
