#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void printAll(FILE *pFile);

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

    ////// modify cat 

    ////// pwd
    ////// look at the commnad list
    ////// look at the commmands -l  -wall    {if statement}
    /////
    ////[		cp		dd		expr		launchctl	mkdir		pwd		sleep		test
    //bash		csh		df		hostname	link		mv		rm		stty		unlink
    //cat		dash		echo		kill		ln		pax		rmdir		sync		wait4path
    //chmod		date		ed		ksh		ls		ps		sh		tcsh		zsh





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
        int x=0;
            while ((s = strsep(&tmp, " ")) != NULL ) {
                if(x==0) {
                    if (strcmp(s, "exit") == 0 || strcmp(s, "exit\n") == 0) {
                        if(cnt==1)
                        exit(0);
                        else
                            printf("%s","ERROR");
//                            errorMessage();
                    } else if ((strcmp(s, "ls") == 0 || strcmp(s, "ls\n") == 0)&& cnt == 1) {
                        commandNow = 1;
                        rc = fork();
                    } else if (strcmp(s, "cd") == 0) {
                        commandNow = 2;
                        if(cnt == 2)
                        rc = fork();
                        else
                            printf("%s","ERROR");
//                            errorMessage();
                    }else if (strcmp(s, "cat") == 0){
                        commandNow = 3;
                        if(cnt == 2)
                            rc = fork();
                        else
                            printf("%s","ERROR");
//                            errorMessage();
                    }
                    if (rc == 0) {
//                printf("child pid: %d %d\n", (int) getpid(), x);
                        char *cmd_argv[10];
                        if (commandNow == 1) {
                            cmd_argv[0] = strdup("/bin/ls");
                            cmd_argv[1] = NULL;
                            execv(cmd_argv[0], cmd_argv);
                        } else if (commandNow == 2) {
                            char* path;

                            while ((path = strsep(&arguments[1], "\n")) != NULL ) {
                                break;
                            }

                                if (chdir(path) == -1) {
                                printf("%s", arguments[1]);
                                printf("%s\n", "error");
                                return 0;
                            }
                        }else if (commandNow == 3){
                            char* path;
                            while ((path = strsep(&arguments[1], "\n")) != NULL ) {
                                break;
                            }
                            FILE* fp = fopen(path, "r");
                            printAll(fp);
                        }
// do some set up work
//                (void) close(STDOUT_FILENO); // no longer can print to the screen
//                open("output.txt", O_WRONLY | O_CREAT | O_TRUNC);
// if successful, doesn't return
//                        printf("failed!\n");
                    }

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

void printAll(FILE *fp) {
    char * line = NULL;
    size_t len = 0;
    if (fp == NULL){
        exit(EXIT_FAILURE);
    }
    while ((getline(&line, &len, fp)) != -1) {
        printf("%s", line);
    }
}
