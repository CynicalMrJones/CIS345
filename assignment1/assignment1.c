
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]){
    int pid = fork();
    char promptDir[1024];
    getcwd(promptDir, sizeof(char[1024]));

    while(1){
        if (pid == 0) {
            //Child Process
            char buf[1024];
            char currentDir[1024];
            char exeDir[1024] = "/bin/";
            char *token;
            char *arr[10];
            int i = 1;

            //gets current directory and prints it as a shell prompt
            printf("%s$", promptDir);
            getcwd(currentDir, sizeof(char[1024]));

            //get user input 
            fgets(buf, 1024, stdin);
            //fgets puts a \n char at the end of buff. 
            //This code removes it
            buf[strcspn(buf, "\n")] = 0;
            //check to see if we need to exit the program
            if(strcmp(buf,"quit") == 0){
                kill(pid, 9);
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
            if(execv(exeDir, arr) == -1){
                //ABSOLUTLY DISGUSING CONDITIONAL STATEMENT
                if((strcmp(arr[0], "cd") != 0) && (strcmp(arr[0], "path") != 0) 
                        &&(strcmp(arr[0], "quit") != 0)){
                    printf("Command not found\n");
                }
                else{
                    //handle the cd command
                    if(strcmp(arr[0], "cd") == 0){
                        strcat(currentDir,"/");
                        strcat(currentDir,arr[1]);
                        //Error handling for change dir
                        if(chdir(currentDir) == -1){
                            printf("No such file or DIR...%s\n", currentDir);
                        }
                        else{
                            getcwd(promptDir, sizeof(char[1024]));
                        }
                    }

                //Handling the PATH command
                if(strcmp(arr[0], "path") == 0){
                    if(strcmp(arr[1], "+") == 0){
                        strcat(exeDir, arr[2]);
                        printf("New EXE Path: %s\n", exeDir);
                    }
                    else if(strcmp(arr[0], "-") == 0){

                    }
                }
                }
            } 
            else{
                printf("Command not found\n");
            }
        }
        else {
            //Parent process
            waitpid(pid, WIFEXITED(1), 0);
            printf("Hello from parent\n");
            exit(0);
        }
    }
}
