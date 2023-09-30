#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/fcntl.h>

void pathCommand(char *pString[5]);

//void printAll(FILE *pFile);
void errMessage(){
    char error_message[30] = "An error has occurred\n";
    write(STDERR_FILENO, error_message, strlen(error_message));
}
char *paths[100];
int rediFile=-1;
int stdout_fd=-1;
//int stdout_copy;
void allCommand( char *cmd_argv[10],char *args[] , char *command,bool redi ){
    int i = 1;

    for (; i < 100; ++i) {
        if(redi){
            if(strcmp(args[i],">") == 0 ){
                cmd_argv[i] = NULL;
                break;
            }
        }
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
    int is_executed = 0;
    for (int j = 0; j < 100; ++j) {
        char result[100];
        if(paths[j]!=NULL)
        strcpy(result,paths[j]);
        strcat(result,command);
        cmd_argv[0] = result;
        if (access(result, X_OK) == 0){
            is_executed = 1;
            if(redi == true){
                while ((args[i+1] = strdup(strsep(&args[i+1], "\n"))) != NULL) {
                    break;
                }
//                (void) close(STDOUT_FILENO);

//                open(  args[i+1], O_CREAT|O_TRUNC|O_RDWR|O_APPEND,S_IRWXU);
//                puts("maaaaan");
//                int cc = fork();
                if(fork()  == 0) {
                    stdout_fd = dup(STDOUT_FILENO);
//                    close(STDOUT_FILENO);
                    rediFile = open(args[i + 1], O_CREAT | O_TRUNC | O_RDWR | O_APPEND, S_IRWXU);
                    dup2(rediFile, STDOUT_FILENO);
//                    close(rediFile);
                    execv(result, cmd_argv);
                }
                wait(0);
                dup2(stdout_fd, STDOUT_FILENO);

            }
            else{
                if(fork()  == 0) {
                    execv(result, cmd_argv);
                }
                wait(0);
            }
//            execv(result, cmd_argv);

        }
        if(paths[j]==NULL)break;


//        else{
////            printf("%s", command);
//        }
    }
    if(is_executed == 0)
    errMessage();

}
//void fromFile(FILE *fp) {
//    char * line = NULL;
//    size_t len = 0;
//    fp = fopen("database.txt", "r");
//    if (fp == NULL){
//        exit(EXIT_FAILURE);
//    }
//    while ((getline(&line, &len, fp)) != -1) {
//        printf("%s", line);
//    }
//}
int main(int argc , char *argv[]) {

    paths[0] = "/bin/";

    char *text = NULL;
    size_t lengh=0;
    char*s;
    int rc = -1;
    int commandNow = -1;
    ///// cd done
    ///// ls done
    ///// exit done
    ///// exit issue Done
    ////// look at the commmands -l  -wall    {if statement}    Done
    ////// path Done
    ////// batch mode Done



    ////// redirection
    ///// remainng redirection
    FILE *fp;

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

    bool isRedirect = false;
    while(getline(&text ,&lengh,fp)){
        commandNow = -1;
        int mxCnt = 10e5;
        if(text == NULL)continue;
        char* tmp = strdup(text);
        char* cntString = strdup(text);
        int cnt=0;
        char* arguments[100];
        while ((s = strsep(&cntString, " ")) != NULL ) {
            if(strcmp(s,  "\0") == 0 || strcmp(s,  "\n") == 0) {
                continue;
            }
                arguments[cnt]=s;
                cnt++;
            if(strcmp(s,">") == 0){
                if(isRedirect == false)
                mxCnt = cnt+1;
                isRedirect = true;
            }
        }
        if(cnt > mxCnt){
            if(fp == stdin)
                printf("wish> ");
            continue;
        }
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
                    else if (strcmp(s, "cd") == 0 || strcmp(s, "cd\n") == 0) {
                        if(cnt == 2){
                            commandNow = 2;
                        }
//                        rc = fork();
                        else{
                            errMessage();
                        }
                    }
                    else if (strcmp(s, "path") == 0 || strcmp(s, "path\n") == 0){
                        commandNow = 3;
//                        rc = fork();
                    }
                    else{

                            commandNow = 1;
//                            rc = fork();

                    }
//                    if (rc == 0) {
                        char *cmd_argv[10];
                        if (commandNow == 1) {
                            bool red = false;
                            if (isRedirect)
                                red = true;
                            isRedirect = false;
                            allCommand(cmd_argv, arguments, arguments[0], red);

                            if (red) close(rediFile);
                            break;
                        }
//                        break;

//                    }

                        if (commandNow == 2) {
                            char *path;
                            while ((path = strsep(&arguments[1], "\n")) != NULL) {
                                break;
                            }
                            if (chdir(path) == -1) {
                                errMessage();
                            }
                        }
                        else if (commandNow == 3) {
                            pathCommand(arguments);
                        }
                    }


                break;
                x++;
        }
        wait(0);

        if(strcmp(text,"exit\n") == 0){
            exit(0);
        }
        if(fp == stdin)
        printf("wish> ");
    }

    return 0;
}

void pathCommand(char *pString[100]) {
    memset(paths, 0, sizeof paths);
    if(pString[1] == NULL){
        return;
    }

    int i = 1;
    for (; i < 100; ++i) {
        if(pString[i] == NULL){
            break;
        }
        char *p = strdup(pString[i]);
        while ((pString[i] = strdup(strsep(&p, "\n"))) != NULL) {
            break;
        }
        paths[i-1] = pString[i];
        if(pString[i][strlen(pString[i])-1] != '/') {
            strcat(paths[i - 1], "/");
        }
    }
}


//path tests
//p1.sh
//path
//p1.sh
//ls
//exit