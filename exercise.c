#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define BUFSIZE 256
#define ALLOWED_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789/_-."

// Whitelist function to sanitize file path
void sanitize_path(char *path) {
    char *p = path;
    while (*p) {
        if (!strchr(ALLOWED_CHARS, *p)) {
            *p = '_'; // replace disallowed characters with underscore
        }
        p++;
    }
}

// This program prints the size of a specified file in bytes
int main(int argc, char** argv) {
    // Ensure that the user supplied exactly one command line argument
    if (argc != 2) {
      fprintf(stderr, "Please provide the address of a file as an input.\n");
      return -1;
    }

    char sanitized_path[BUFSIZE];
    strncpy(sanitized_path, argv[1], BUFSIZE - 1);
    sanitized_path[BUFSIZE - 1] = '\0';

    sanitize_path(sanitized_path);

    char cmd[BUFSIZE] = "wc -c < ";

    // unsigned integer for objects size
    size_t buffer_left = BUFSIZE - strlen(cmd) - 1;

    // Append sanitized user input to the command string
    strncat(cmd, sanitized_path, buffer_left);
    cmd[BUFSIZE - 1] = '\0';  // must end in null character

    // copy to separate buffer
    char command[BUFSIZE];
    strncpy(command, cmd, BUFSIZE - 1);
    command[BUFSIZE -1] = '\0';

    system(command);
}
