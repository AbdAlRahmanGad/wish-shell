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

//    paths[0] = "/bin/";
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
void fromFile(FILE *fp) {
    char * line = NULL;
    size_t len = 0;
    fp = fopen("database.txt", "r");
    if (fp == NULL){
        exit(EXIT_FAILURE);
    }
    while ((getline(&line, &len, fp)) != -1) {
        printf("%s", line);
    }
}
int main(int argc , char *argv[]) {

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
    ////// path Done

    ////// batch mode Done
    ////// redirection


    ///// remainng batch mode and redirection
    FILE *fp = stdin;

    if(argc==2){
        fp = fopen(argv[1], "r");
        if (fp == NULL){
            exit(EXIT_FAILURE);
        }
    }
    else
        fp = stdin;
    if(fp == stdin)
        printf("wish> ");
    while(getline(&text ,&lengh,fp) != -1){
        char* tmp = strdup(text);
        char* cntString = strdup(text);
        int cnt=0;
        char* arguments[100];
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
                    else if (strcmp(s, "path") == 0 || strcmp(s, "path\n") == 0){
                        commandNow = 5;
                        rc = fork();
                    }
//                    else if(strcmp(s, "path\n") == 0)
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
        if(fp == stdin)
        printf("wish> ");
//        else
//            return 0;
    }

    return 0;
}

///// remainng Path Commands and check '/' in path commands and pathc mode and redirection

void pathCommand(char *pString[100]) {
    memset(paths, 0, sizeof paths);

//    if(pString[1]){}
//    printf("%s",pString[0]);
    if(pString[1] == NULL){
        return;
    }
//    printf("%s",pString[1]);
    int i = 1;

//    char end_char = file_name[strlen(file_name)-1];
//    strlen(paths[i]);
//    i = 5;
    for (; i < 100; ++i) {
        if(pString[i] == NULL){
            break;
        }
        char *p = strdup(pString[i]);
        while ((pString[i] = strdup(strsep(&p, "\n"))) != NULL) {
            break;
        }
//        if(pString[i][strlen(pString[i])-1] != '/'){
////            char result[100];
////            strcpy(paths[i],pString[i]);
////            paths[i] = result;
//        }
//        else
        paths[i-1] = pString[i];
        if(pString[i][strlen(pString[i])-1] != '/') {
            strcat(paths[i - 1], "/");
        }
    }
//    char *p = strdup(paths[i - 2]);
//    while ((paths[i - 2] = strdup(strsep(&p, "\n"))) != NULL) {
//        break;
//    }
//    for (int i = 0; i < 100; ++i) {
//        if(paths[i] == NULL){
//            break;
//        }
//        printf("%s ", paths[i]);
//    }
//    printf("%s", paths[0]);
////    printf("%s", pString[0]);
//    printf("%s", paths[1]);
////    printf("%s", pString[1]);
//    printf("%s", paths[2]);
////    printf("%s", pString[2]);
//    printf("%s", paths[3]);
//    printf("%s", pString[3]);

    //    Important: Note that the shell itself does not implement ls or other commands
        //    (except built-ins).
        //    All it does is find those executables in one of the
        //    directories specified by path and create a new process to run them.
//            To check if a particular file exists in a directory and is executable,
//            consider the access() system call. For example, when the user types ls,
//            and path is set to include both /bin and /usr/bin, try access("/bin/ls", X_OK).
//            If that fails, try "/usr/bin/ls". If that fails too, it is an error.

//            Your initial shell path should contain one directory: /bin
//if
///  0 or more commands
///  always override
///

//    paths

//if (access("/bin/ls", X_OK)){

//}
//    path /bin /usr/bin
}
