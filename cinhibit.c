/*
    CInhibit - Prevent accidental execution of certain commands
    Simplified C port of the Inhibit project
    Copyright (c) 2024 by Ralf Kilian
    Distributed under the MIT License (https://opensource.org/licenses/MIT)

    GitHub: https://github.com/urbanware-org/cinhibit
    GitLab: https://gitlab.com/urbanware-org/cinhibit
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <readline/readline.h>
#include <readline/history.h>

#define HOSTNAME_MAX 256
#define VERSION "1.0.0"

int main(int argc, char **argv) {

    char hostname[HOSTNAME_MAX];
    
    if (argc != 2) {
        printf("usage: cinhibit [--version] \"COMMAND\"\n");
        return 1;
    }
    if (strcmp(argv[1], "--version") == 0) {
        printf("%s\n", VERSION);
        return 0;
    }   
    
    printf("\n" \
        "####  ##    ##  ##    ##  ####  #######   ####  ########  ########  #######\n" \
        " ##   ###   ##  ##    ##   ##   ##    ##   ##      ##     ##        ##    ##\n" \
        " ##   ####  ##  ##    ##   ##   ##    ##   ##      ##     ##        ##    ##\n" \
        " ##   ## ## ##  ########   ##   #######    ##      ##     ######    ##    ##\n" \
        " ##   ##  ####  ##    ##   ##   ##    ##   ##      ##     ##        ##    ##\n" \
        " ##   ##   ###  ##    ##   ##   ##    ##   ##      ##     ##        ##    ##\n" \
        "####  ##    ##  ##    ##  ####  #######   ####     ##     ########  #######\n");
    
    printf("\nWarning! The '%s' command has been inhibited!\n", argv[1]);
    printf("\nIn order to proceed you have to confirm the process.\n\n");

    gethostname(hostname, HOSTNAME_MAX - 1);
    printf("Hostname: %s\n", hostname);

    char *line = readline("Confirm:  ");
    
    if (strncmp(line, hostname, HOSTNAME_MAX) != 0) {
        printf("\nConfirmation failed. Process canceled.\n\n");
        free(line);
        return 1;
    }

    printf("\nConfirmation successful. Proceeding.\n\n");
    system(argv[1]);
    
    free(line);
    return 0;
    
}
