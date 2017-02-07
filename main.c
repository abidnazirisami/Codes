#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void lifetimeLoop();
void getArgsFromLine(int *argc, char *line, char args[100][100]);
int execute (char ** arg, int in, int out, int background);
int executeIt (int argc, char args[100][100]);
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
void executeEcho(char **arg) {
    int i;
    for (i=1; arg[i] != NULL; i++) printf("%s ", arg[i]);
    printf("\n");
}
void executeHelp() {
    printf("You can do anything here.\n");
    printf("I won't tell you how to do it.\n");
    printf("You have to figure it out yourself.\n");
    printf("Check www.google.com for more\n");
    printf("List of builtin functions:\n");
    printf("cd\npwd\nExit\nEcho\nHelp");
}
int execute (char ** arg, int in, int out, int background) {
    pid_t pid, wpid;
    int status;
    if (strcmp(arg[0], "cd") == 0) executeCD(arg[1]);
        else if (strcmp(arg[0], "echo") == 0) executeEcho(arg);
        else if (strcmp(arg[0], "pwd") == 0) executePwd();
        else if (strcmp(arg[0], "help") == 0) executeHelp();
        else if (strcmp(arg[0], "exit") == 0) executeExit();
    else {
        pid = fork();

        if (pid == 0) {
            // Child process
            if(in!=0)	{
				dup2(in,0);
				close(in);
			}
			if(out!=1)	{
				dup2(out,1);
				close(out);
            }
            if (execvp(arg[0], arg) == -1) {
                perror("Error: ");
            }
            exit(EXIT_FAILURE);
        }

        else if (pid < 0) perror("Error occured while forking"); // well, it explains itself
        else {
        // Parent process
		if (!background) {
			do {
          			wpid = waitpid(pid, &status, WUNTRACED);
        		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
      }
    }
    return 1;
}
int executeIt (int argc, char args[100][100]) {
    char **arg[100];
    int in, out, background;
    int pipefd[2];
    in = 0;
    out = 1;
    background = 0;
    memset(arg, 0, sizeof arg);
    int i = 0;
    int cmdptr = 0;
    if (args[argc-1][0] == '&') {
        argc--;
        background = 1;
    }
    for (i=0; i<argc; i++) {
	//printf("%s\n", args[i]);
        if (args[i][0] == '|') {
            arg[cmdptr] = NULL;
            pipe(pipefd);
            execute (arg, in, pipefd[1], background);
            in = pipefd[0];
            close(pipefd[1]);
            cmdptr = 0;
        }
        else if (args[i][0] == '<') {
		in=open(args[i+1], O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
		arg[cmdptr]=NULL;
        }
        else if (strcmp(args[i], ">>") == 0) {
			out=open(args[i+1], O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR);
			arg[cmdptr]=NULL;
			break;
        }
        else if (args[i][0] == '>') {
		//printf("asfasf\n");
		out=open(args[i+1], O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
		arg[cmdptr]=NULL;
		//printf("%s\n", args[i+1]);
		break;
        }

        else {
            arg[cmdptr] = args[i];
            cmdptr++;
        }
    }
    arg[cmdptr] = 0;
    execute(arg, in, out, background);
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
    char line[10000],  args[100][100];
    memset(line, 0, sizeof line);
    memset(args, 0, sizeof args);
    while (isRunning) {
        printf(">> ");
        gets(line);
        argc = 0;
        getArgsFromLine(&argc, line, args);
        int i;
        isRunning = executeIt(argc, args);
        memset(line, 0, sizeof line);
        memset(args, 0, sizeof args);
    }

}

int main(int argc, char **argv) {
    printf("Welcome to the Hogwarts School of WitchcraftWizardry\n\n");
  // Running the lifetime loop
    lifetimeLoop();
  // the loop terminated, returning exit status
    return 0;
}
