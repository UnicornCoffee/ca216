#include <stdio.h>
#include <string.h>
#include "shell.h"

// Parse user input into arguments
void parse_input(char *input, char *args[]) {
    char *token;
    int i = 0;
    token = strtok(input, " \t\n");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL; // Null-terminate the argument list
}

// Print error message
void print_error(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
}

// Check if a file exists
int file_exists(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return 1; // File exists
    }
    return 0; // File does not exist
}
