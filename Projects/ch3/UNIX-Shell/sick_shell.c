#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE 80 /* The maximum length command */

int execChild(char **args, int sz) {
    
    const char *childProcess = args[0];
    int res;
    if(sz >= 2){
        
        if(res = execvp(childProcess, args+1) < 0){
            fprintf(stderr, "EXEC Failed\n");
            exit(1);
        }
    }
    else{
        if(res = execvp(childProcess, NULL) < 0){
            fprintf(stderr, "EXEC Failed\n");
            exit(1);
        }

    }

    return res;

}

int formArgs(char **args, char *line) {

    int ptr = 0;
    int i = 0;

    // printf("%d\n",strlen(line));

    while(i<strlen(line) && line[i] != '\n'){
        int j = 0;
        while(line[i + j] != ' ' && line[i + j] != '\n' && (i + j) < strlen(line)){
            j++;
        }
        // printf("%d %d\n", i, j);
        char *curArg = (char *)malloc(j + 1);
        strncpy(curArg, line + i, j);
        curArg[j] = '\0';

        args[ptr] = curArg;

        j++;
        i += j;
        ptr++;
    }
    args[ptr] = NULL;
    return ptr;
}

int main(void)
{
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    int shouldRun = 1; /* flag to determine when to exit program */

    while (shouldRun) {
        char line[80];
        printf("osh>");
        fflush(stdout);

        fgets(line, sizeof(line), stdin);

        // printf("You entered\n%s\n", line);
        int sz = formArgs(args, line);
        int i = 0;

        // for(;i<sz;i++){
        //     printf("%d: %s\n", i, args[i]);
        // }

        if(sz==1 && strcmp(args[0], "exit\0")==0){
            shouldRun = 0;
            continue;
        }

        pid_t pid = fork();

        if(pid < 0){
            fprintf(stderr, "Fork Failed\n");
        }
        else if(pid==0){
            // printf("%s\n", args[0])
            
            int ret = execChild(args, sz);
            // if(ret != 0){
            //     printf("Process exited with error %d", ret);
            // }
        }
        else{
            wait(NULL);
        }

        
    }

    return 0;
}