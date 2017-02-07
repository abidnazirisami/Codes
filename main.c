#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
void lifetimeLoop();
void getArgsFromLine(int *argc, char *line, char args[100][100]);
int execute (int argc, char args[100][100]);
void executeCD(char args[100]);
void executeEcho();
void executePwd();
void executeHelp();
void executeExit();
void getInput();
void printOutput();
void executePwd () {
    char str[1000];
    printf("You are currently here: %s\n", getcwd(str, 1000));
}
void executeCD(char args[100]) {
    chdir(args);
}
void executeExit() {
    printf("Good bye, cruel world.\n");
    exit(EXIT_SUCCESS);
}
void executeEcho(int argc, char args[100][100]) {
    for (int i=1; i<argc; i++) printf("%s ", args[i]);
    printf("\n");
    printf("That was pretty easy. Try again, ayyo, lmao\n");
}
void executeHelp() {
    printf("You can do anything here.\n");
    printf("I won't tell you how to do it.\n");
    printf("You have to figure it out yourself.\n");
    printf("Check www.google.com for more\n");
}
int execute (int argc, char args[100][100]) {
    pid_t pid, wpid;
    int status;
    pid = fork();
    char **arg[100];
    if (pid == 0) {
        // Child process
        //system(args[0]);
        int i;
        memset(arg, 0, sizeof arg);
        //for (i=0; i<10; i++) printf("%d\n", arg[i]);
        for (i=0; i<argc; i++) {
            arg[i] = args[i];
            //printf("%d\n", arg[i]);
        }
        //for (i=0; i<10; i++) printf("%p %s\n", arg[i], arg[i]);

        //printf("1");
        //printf("%s\n", arg[1]);
        //if (strlen(arg[1]) == 0)
            //arg[1] = 0;
        //arg[2] = 0;
        if (execvp(arg[0], arg) == -1) {
            perror("Error: ");
        }
        exit(EXIT_FAILURE);
    }

    else if (pid < 0) perror("Error occured while forking"); // well, it explains itself
    else {
    // Parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}


void getArgsFromLine(int *argc, char *line, char args[100][100]) {
    int ptr = 0; // this variable will be used to iterate over the line
    int argcnt = 0; // this variable will be used to keep count of the arguments found in the line
    int argptr = 0; // this variable will be used to parse each individual arguments
    memset(args, 0, sizeof args);
    while (line[ptr] != 0) {
        if (line[ptr] == ' ') {
            args[argcnt][argptr] = 0;
            argcnt++;
            argptr = 0;
        }
        else {
            args[argcnt][argptr++] = line[ptr];
        }
        ptr++;
    }
    *argc = ++argcnt;
}
void lifetimeLoop() {
    int isRunning = 1;
    int argc;
    char line[100],  args[100][100];
    memset(args, 0, sizeof 0);
    while (isRunning) {
        printf(">> ");
        gets(line);
        argc = 0;
        getArgsFromLine(&argc, line, args);
        int i;
        if (strcmp(args[0], "cd") == 0) executeCD(args[1]);
        else if (strcmp(args[0], "echo") == 0) executeEcho(argc, args);
        else if (strcmp(args[0], "pwd") == 0) executePwd();
        else if (strcmp(args[0], "help") == 0) executeHelp();
        else if (strcmp(args[0], "exit") == 0) executeExit();
        else isRunning = execute(argc, args);
    }

}

int main(int argc, char **argv) {
    printf("Welcome to the Hogwarts School of WitchcraftWizardry\n\n");
  // Running the lifetime loop
    lifetimeLoop();
  // the loop terminated, returning exit status
    return 0;
}
