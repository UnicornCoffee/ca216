#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "shell.h"

/*
    These functions handle input and output redirection for the shell environment. 

    - handle_input_redirection: Opens the specified input file and redirects standard input to it.
    
    - handle_output_redirection: Opens or creates the specified output file, truncating it if it already exists, and redirects standard output to it.

    - handle_output_redirection_append: Opens or creates the specified output file, appending to it if it already exists, and redirects standard output to it.
*/



// Function to handle input redirection
void handle_input_redirection(char *input_file) {
    int fd = open(input_file, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDIN_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

// Function to handle output redirection (truncate)
void handle_output_redirection(char *output_file) {
    int fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fd);
}

// Function to handle output redirection (append)
void handle_output_redirection_append(char *output_file) {
    int fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        exit(EXIT_FAILURE);
    }
    close(fd);
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
