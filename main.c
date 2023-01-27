#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void handleExternal() {

}

int main(void) {
    char s[2048];
    char** commands;
    commands = (char**)malloc(128*sizeof(char*));

    while("Yo Mama") {
        printf("mush$ ");
        fflush(stdout);
        fgets(s, sizeof s, stdin);
        char *token;
        int count = 0;
        if ((token = strtok(s, " \t\n\r")) != NULL) {
            do {
                commands[count] = token;
                count++;
            } while ((token = strtok(NULL, " \t\n\r")) != NULL);
        }
        commands[count] = NULL;

        if (strcmp(commands[0],"cd") == 0) {
            int d;
            d = chdir(commands[1]);
            if (d == -1) {
                perror("cd");
            }
        } else if (strcmp(commands[0],"exit") == 0) {
            exit(0);
        }else {
            pid_t pid = fork();
            if (pid == 0) {
                execvp(commands[0], commands);
                perror("exec");
                exit(1);
            } else {
                wait(NULL);
            }
        }
    }
    return 0;
}