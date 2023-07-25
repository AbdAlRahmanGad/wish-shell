#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

//void printAll(FILE *pFile);
void errMessage(){
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
}
void lsCommand( char *cmd_argv[10],char *args[]){
        char *binaryPath = "/bin/ls";

    cmd_argv[0] = binaryPath;
    int i = 1;
    for (; i < 5; ++i) {
        if(args[i]== NULL){
            cmd_argv[i] = NULL;
            break;
        }
        cmd_argv[i] = args[i];
    }
    char* path =  strdup(cmd_argv[i-1]);
    while ((cmd_argv[i-1] = strdup(strsep(&path, "\n"))) != NULL ) {
        break;
    }
cmd_argv[0]="ls";
    execv(binaryPath, cmd_argv);
}
void catCommand( char *cmd_argv[10],char *args[]){
    char *binaryPath = "/bin/cat";
    cmd_argv[0] = binaryPath;
    int i = 1;
    for (; i < 5; ++i) {
        if(args[i]== NULL){
            cmd_argv[i] = NULL;
            break;
        }
        cmd_argv[i] = args[i];
    }
    char* path =  strdup(cmd_argv[i-1]);
    while ((cmd_argv[i-1] = strdup(strsep(&path, "\n"))) != NULL ) {
        break;
    }
    cmd_argv[i]= NULL;
    execv(binaryPath, cmd_argv);

}
void pwdCommand( char *cmd_argv[10]){
    char *binaryPath = "/bin/pwd";
    cmd_argv[0] = binaryPath;
    cmd_argv[1] = NULL;
    execv(binaryPath, cmd_argv);
}
int main(int argc , char *argv[]) {
    printf("wish> ");
    char *text = NULL;
    size_t lengh=0;
    char*s;
    int rc;
    int commandNow = -1;
    ///// cd done
    ///// ls done
    ///// exit done
    ////// cat done


    ////// pwd
    ////// look at the commnad list
    ////// look at the commmands -l  -wall    {if statement}
    /////
    ////[
    /// 	cp		mkdir		pwd
    //mv		rm
    //cat			rmdir
    //cls





    ///// batch mode
    while(getline(&text ,&lengh,stdin)){
        char* tmp = strdup(text);
        char* cntString = strdup(text);
        int cnt=0;
        char* arguments[5];
        while ((s = strsep(&cntString, " ")) != NULL ) {
            arguments[cnt]=s;
            cnt++;
        }
        arguments[cnt] = NULL;
        int x=0;
            while ((s = strsep(&tmp, " ")) != NULL ) {
                if(x==0) {
                    if (strcmp(s, "exit") == 0 || strcmp(s, "exit\n") == 0) {
                        if(cnt==1)
                        exit(0);
                        else
                            printf("%s","ERROR");
//                            errorMessage();
                    } else if ((strcmp(s, "ls") == 0 || strcmp(s, "ls\n") == 0)) {
                        commandNow = 1;
                        rc = fork();
                    } else if (strcmp(s, "cd") == 0) {
                        commandNow = 2;
                        if(cnt == 2)
                        rc = fork();
//                        else
//                            printf("%s","ERROR");
//                            errorMessage();
                    }else if (strcmp(s, "cat") == 0){
                        commandNow = 3;
                            rc = fork();
//                        else
//                            printf("%s","ERROR");
//                            errorMessage();
                    }else if ((strcmp(s, "pwd") ==0||strcmp(s, "pwd\n")== 0) && cnt == 1){
                        commandNow = 4;
                        rc = fork();

                    }
                    if (rc == 0) {
                        char *cmd_argv[10];
                        if (commandNow == 1) {
                            lsCommand(cmd_argv,arguments);
                        } else if (commandNow == 2) {
                            char* path;
                            while ((path = strsep(&arguments[1], "\n")) != NULL ) {
                                break;
                            }
                                if (chdir(path) == -1) {
                                    errMessage();
                            }
                        }else if (commandNow == 3){
//                            char* path;
//                            while ((path = strsep(&arguments[1], "\n")) != NULL ) {
//                                break;
//                            }
                            catCommand(cmd_argv,arguments);
//                            FILE* fp = fopen(path, "r");
//                            printAll(fp);
                        }else if (commandNow == 4){
                            pwdCommand(cmd_argv);
                        }
// do some set up work
//                (void) close(STDOUT_FILENO); // no longer can print to the screen
//                open("output.txt", O_WRONLY | O_CREAT | O_TRUNC);
// if successful, doesn't return
//                        printf("failed!\n");
                    }
/// repository
                }x++;
        }
        if(strcmp(text,"exit\n") == 0){
            exit(0);
        }
        wait(0);
        printf("wish> ");

    }
    return 0;
}


//void printAll(FILE *fp) {
//    char * line = NULL;
//    size_t len = 0;
//    if (fp == NULL){
//        exit(EXIT_FAILURE);
//    }
//    while ((getline(&line, &len, fp)) != -1) {
//        printf("%s", line);
//    }
//}
