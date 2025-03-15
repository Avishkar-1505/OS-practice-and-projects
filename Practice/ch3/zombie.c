#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
    pid_t pid;

    pid = fork();

    if(pid<0){
        fprintf(stderr, "Fork Failed");
        return 1;
    }
    else if(pid==0){
        printf("Child\n");
        return 0;
    }
    else{
        sleep(20);
        wait(NULL);
        printf("Done\n");
    }

    return 0;
}

