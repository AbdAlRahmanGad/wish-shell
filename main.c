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
    char* path =  strdup(cmd_argv[i-1]);
    while ((cmd_argv[i-1] = strdup(strsep(&path, "\n"))) != NULL ) {
        break;
    }
//    cmd_argv[0]= command;

//    char *binaryPath = "/bin/";

//    cmd_argv[0] = binaryPath;
    for (int j = 0; j < 1; ++j) {
        paths[0] = "/bin";
        paths[0] = "/usr";
        command = "/ls";
        cmd_argv[0] = strcat(paths[j],command);
        execv(cmd_argv[0], cmd_argv);
        printf("%s\n ",cmd_argv[0]);


    }
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
    ////// pwd Done
    /////   exit issue Done

    /////   path  ?????????????????????????????????????????????????????????????????????

    ////// look at the commnad list
    ////// look at the commmands -l  -wall    {if statement}

    ////// batch mode
    ////// redirection


    /// 	cp		mkdir		pwd
    //mv		rm
    //cat			rmdir
    //cls


//    access(


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
                    } else if ((strcmp(s, "ls") == 0 || strcmp(s, "ls\n") == 0)) {
                        commandNow = 1;
                        rc = fork();
                    } else if (strcmp(s, "cd") == 0) {
                        commandNow = 2;
                        if(cnt == 2)
                        rc = fork();
                    }else if (strcmp(s, "cat") == 0){
                        commandNow = 3;
                            rc = fork();
                    }else if ((strcmp(s, "pwd") ==0||strcmp(s, "pwd\n")== 0) && cnt == 1){
                        commandNow = 4;
                        rc = fork();

                    }else if (strcmp(s, "path") == 0){
                        commandNow = 5;
                        rc = fork();
                    }
                    if (rc == 0) {
                        char *cmd_argv[10];
                        if (commandNow == 1) {
//                            lsCommand(cmd_argv,arguments);
                            allCommand(cmd_argv,arguments,arguments[0]);
                        } else if (commandNow == 2) {
                            char* path;
                            while ((path = strsep(&arguments[1], "\n")) != NULL ) {
                                break;
                            }
                                if (chdir(path) == -1) {
                                    errMessage();
                            }
                        }else if (commandNow == 3){
                            catCommand(cmd_argv,arguments);
                        }else if (commandNow == 4){
                            pwdCommand(cmd_argv);
                        }
                        else if (commandNow == 5){
                            pathCommand(arguments);
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
