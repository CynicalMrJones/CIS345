
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
    int pid = fork();
    while(1){

        if (pid == 0) {
            //Child Process
            char buf[1024];
            char prevDir[1024];
            char currentDir[1024];
            char exeDir[1024] = "/bin/";
            char *token;
            char *arr[10];
            int i = 1;

            //gets current directory and prints it as a shell prompt
            getcwd(currentDir, sizeof(char[1024]));
            printf("%s$", currentDir);

            //get user input 
            fgets(buf, 1024, stdin);
            //fgets puts a \n char at the end of buff. 
            //This code removes it
            buf[strcspn(buf, "\n")] = 0;
            //check to see if we need to exit the program
            if(strcmp(buf,"quit") == 0){
                exit(1);
            }
            // tokenizes the input
            token = strtok(buf," ");
            arr[0] = token;
            strcat(exeDir, token);
            //fills and array with all the args
            while(token != NULL){
                token = strtok(NULL, " ");
                arr[i] = token;
                i++;
            }
            for(i = i; i< 10;i++){
                arr[i] = NULL;
            }
            //handle the cd command
            //Leaving off here
            if(strcmp(arr[0], "cd") == 0){
                strcpy(prevDir, currentDir);
                strcat(currentDir,"/");
                strcat(currentDir,arr[1]);
                chdir(currentDir);
                getcwd(currentDir, sizeof(char[1024]));
            }
            //attempt to execute the command
            execv(exeDir, arr); 
        }
        else {
            //Parent process
            waitpid(pid, WIFEXITED(1), 0);
            printf("Hello from parent\n");
            exit(0);
        }
    }
}
