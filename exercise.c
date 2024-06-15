#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
                                
#define BUFSIZE 256

// This function escapes characters that pose a security risk as whitespace
void escape_special_chars(char *path) {
    while (*path) {
        if (*path == '&' || *path == '|' || *path == '<' || *path == '>' || *path == '(' || *path == ')' || *path == '{' || *path == '}' || *path == ':') {
            *path = ' ';
        }
        path++;
    }
}

// This program prints the size of a specified file in bytes
int main(int argc, char** argv) {
    // Ensure that the user supplied exactly one command line argument
    if (argc != 2) { 
      fprintf(stderr, "Please provide the address of a file as an input.\n");
      return -1;
    }

    escape_special_chars(argv[1]);
    char cmd[BUFSIZE] = "wc -c < ";    

    // unsigned integer for objects size    
    size_t buffer_left = BUFSIZE - strlen(cmd) - 1;
    
    // Append user input to the command string
    strncat(cmd, argv[1], buffer_left);
    cmd[BUFSIZE - 1] = '\0';  // must end in null character

    // copy to separate buffer
    char command[BUFSIZE];
    strncpy(command, cmd, BUFSIZE - 1);
    command[BUFSIZE -1] = '\0';

    system(command);
}