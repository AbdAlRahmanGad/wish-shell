#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void pathCommand(char *pString[5]);

//void printAll(FILE *pFile);
void errMessage(){
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
}
char *paths[100];
void allCommand( char *cmd_argv[10],char *args[] , char *command){
    int i = 1;
    for (; i < 5; ++i) {
        if(args[i]== NULL){
            cmd_argv[i] = NULL;
            break;
        }
        cmd_argv[i] = args[i];
    }
    char* path =  strdup(command);
    while ((command = strdup(strsep(&path, "\n"))) != NULL ) {
        break;
    }
    if(i!=1) {
        char *p = strdup(cmd_argv[i - 1]);
        while ((cmd_argv[i - 1] = strdup(strsep(&p, "\n"))) != NULL) {
            break;
        }
    }

    paths[0] = "/bin/";
    for (int j = 0; j < 100; ++j) {
        char result[100];
    strcpy(result,paths[j]); // copy string one into the result.
    strcat(result,command);
        cmd_argv[0] = result;

        if (access(result, X_OK) == 0){
            execv(result, cmd_argv);
        }else{
            printf("%s", command);
        }
    }
                printf("%s", "error");

}
int main(int argc , char *argv[]) {
    printf("wish> ");
    paths[0] = "/bin/";

    char *text = NULL;
    size_t lengh=0;
    char*s;
    int rc;
    int commandNow = -1;
    ///// cd done
    ///// ls done
    ///// exit done
    ///// exit issue Done
    ////// look at the commmands -l  -wall    {if statement}    Done

    ////// batch mode
    ////// redirection


///// remainng Path Commands and check '/' in path commands and pathc mode and redirection 
///// remainng Path Commands and check '/' in path commands and pathc mode and redirection 
///// remainng Path Commands and check '/' in path commands and pathc mode and redirection


    ///// batch mode
    while(getline(&text ,&lengh,stdin)){
        char* tmp = strdup(text);
        char* cntString = strdup(text);
        int cnt=0;
        char* arguments[5];
        while ((s = strsep(&cntString, " ")) != NULL ) {
            if(strcmp(s,  "\0") == 0 || strcmp(s,  "\n") == 0)
            {
                continue;
            }
                arguments[cnt]=s;
                cnt++;
        }
//        printf("\n%d",cnt);

        arguments[cnt] = NULL;
        int x=0;
            while ((s = strsep(&tmp, " ")) != NULL ) {
                if(x==0) {
                    if (strcmp(s, "exit") == 0 || strcmp(s, "exit\n") == 0) {
                        if(cnt==1)
                        exit(0);
                        else
                           errMessage();
                    }
                    else if (strcmp(s, "cd") == 0) {
                        commandNow = 2;
                        if(cnt == 2)
                        rc = fork();
                    }
                    else if (strcmp(s, "path") == 0){
                        commandNow = 5;
                        rc = fork();
                    }
                    else{
                        commandNow = 1;
                        rc = fork();
                    }
                    if (rc == 0) {
                        char *cmd_argv[10];
                        if (commandNow == 1) {
                            allCommand(cmd_argv,arguments,arguments[0]);
                        } else if (commandNow == 2) {
                            char *path;
                            while ((path = strsep(&arguments[1], "\n")) != NULL) {
                                break;
                            }
                            if (chdir(path) == -1) {
                                errMessage();
                            }
                        }
                        else if (commandNow == 5) {
                            pathCommand(arguments);
                        }
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

void pathCommand(char *pString[5]) {
    //    Important: Note that the shell itself does not implement ls or other commands (except built-ins).
    //    All it does is find those executables in one of the
    //    directories specified by path and create a new process to run them.
//            To check if a particular file exists in a directory and is executable,
//            consider the access() system call. For example, when the user types ls,
//            and path is set to include both /bin and /usr/bin, try access("/bin/ls", X_OK).
//            If that fails, try "/usr/bin/ls". If that fails too, it is an error.

//            Your initial shell path should contain one directory: /bin
//if
//if (access("/bin/ls", X_OK)){

//}
//    path /bin /usr/bin
}
