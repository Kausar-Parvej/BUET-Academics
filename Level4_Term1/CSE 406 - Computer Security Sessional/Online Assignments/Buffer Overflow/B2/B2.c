#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int foo(char *input) {
    int canary = 0xDEADBEEF; 
    char buffer[480];

    strcpy(buffer, input);

    if (canary != 0xDEADBEEF) {
        printf("Stack corrupted!\n");
        exit(1);
    }

    printf("Returning from foo...\n");
    return 0;
}

int main() {
    FILE *badfile;
    char data[580];

    badfile = fopen("badfile", "r");
    fread(data, sizeof(char), 580 , badfile);
    foo(data);
    printf("Finished main\n");

    return 0;
}
