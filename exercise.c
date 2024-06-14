#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
                                
#define BUFSIZE 256                           

// This program prints the size of a specified file in bytes
int main(int argc, char** argv) {
    // Ensure that the user supplied exactly one command line argument
    if (argc != 2) { 
      fprintf(stderr, "Please provide the address of a file as an input.\n");
      return -1;
    }
    
    struct stat stbuf;    
    // Stat the target to examine its properties
    if (stat(argv[1], &stbuf) == -1) {
        perror("Failed to obtain information about the entry.");
        return EXIT_FAILURE;
    }

    char cmd[BUFSIZE] = "wc -c < ";
    strcat(cmd, argv[1]);
    system(cmd);
}