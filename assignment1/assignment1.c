
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
    int pid = fork();

    if (pid == 0) {
        //Child Process
        char userBuf[1024];
        char currentDir[1024];
        char *exePath = "/usr/bin";
        char *buf;
        //gets current directory and prints it as a shell prompt
        getcwd(currentDir, sizeof(char[1024]));
        printf("%s$", currentDir);

        //get user input
        fgets(buf, 1024, stdin);
        strcat(exePath,buf); 
        printf("%s", buf);
    }
    else {
        //Parent process
        waitpid(-1, WIFEXITED(1), 0);
        printf("Hello from parent\n");
    }
}

