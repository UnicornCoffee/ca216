#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "shell.h"

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

// Help command
void help_command() {
    FILE *help_file = fopen("manual/help.txt", "r");
    if (help_file == NULL) {
        perror("help");
        return;
    }
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), help_file) != NULL) {
        printf("%s", buffer);
    }
    fclose(help_file);
}

// Pause command
void pause_command() {
    printf("Press Enter to continue...\n");
    while (getchar() != '\n');
}

// Quit command
void quit_command() {
    printf("Exiting shell.\n");
    exit(EXIT_SUCCESS);
}
