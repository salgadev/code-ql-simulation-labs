#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define BUFSIZE 256
#define ALLOWED_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789/_-.< >|"

void sanitize_path(char *path) {
    char *p = path;
    while (*p) {
        if (!strchr(ALLOWED_CHARS, *p)) {
            *p = '_'; // replace disallowed characters with underscore
        }
        p++;
    }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        fprintf(stderr, "Please provide the address of a file as an input.\n");
        return -1;
    }

    char sanitized_path[BUFSIZE];
    strncpy(sanitized_path, argv[1], BUFSIZE - 1);
    sanitized_path[BUFSIZE - 1] = '\0';

    char cmd[BUFSIZE] = "wc -c < ";
    size_t buffer_left = BUFSIZE - strlen(cmd) - 1;

    strncat(cmd, sanitized_path, buffer_left);
    cmd[BUFSIZE - 1] = '\0';  // must end in null character

    // sanitize the final command
    sanitize_path(cmd);

    system(cmd);
    return 0;
}
