#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/time.h>

void execChild(const char *name, int argc, char *argv[], struct timeval *current) {
    int fdchild = shm_open(name, O_CREAT | O_RDWR, 0666);

    // printf("child: %d\n", fdchild);

    if(fdchild==-1){
        fprintf(stderr, "child: Creating Shared Memory Failed\n");
        return 3;
    }

    if(ftruncate(fdchild, sizeof(struct timeval)) == -1){
        fprintf(stderr, "child: Failed to truncate shared memory\n");
        return 4;
    }
    
    current = mmap(NULL, sizeof(struct timeval), PROT_READ | PROT_WRITE, MAP_SHARED, fdchild, 0);

    if(current == MAP_FAILED){
        fprintf(stderr, "child: Mapping to shared memory failed\n");
        return 5;
    }

    // printf("Writing time to shared memory\n");

    gettimeofday(current, NULL);

    const char *childProcess = argv[1];
    if(argc > 2){

        if(execvp(childProcess, argv+1) < 0){
            fprintf(stderr, "child: EXEC failed\n");
            exit(1);
        }

    }
    else{
        if(execvp(childProcess, NULL) < 0){
            fprintf(stderr, "child: EXEC failed\n");
            exit(1);
        }
    }

    // printf("child: Current time: %ld\n", current->tv_sec);
}

int main(int argc, char* argv[]){
    if(argc < 2){
        fprintf(stderr, "Invalid number of args\n");
        return 1;
    }

    const char* name = "TIME";
    
    struct timeval *current;
    struct timeval *cur;

    

    pid_t pid = fork();

    if(pid<0){
        fprintf(stderr, "Fork Failed\n");
        return 2;
    }
    else if(pid==0){
        execChild(name, argc, argv, current);
    }
    else{
        wait(NULL);

        int fdmain = shm_open(name, O_RDONLY, 0666);
        if(fdmain==-1){
            fprintf(stderr, "Opening Shared Memory Failed\n");
            return 3;
        }
        // printf("main: %d\n", fdmain);
        cur = mmap(NULL, sizeof(struct timeval), PROT_READ, MAP_SHARED, fdmain, 0);

        if(cur == MAP_FAILED){
            fprintf(stderr, "main: Mapping to shared memory failed\n");
            return 5;
        }


        struct timeval res;
        gettimeofday(&res, NULL);
        // printf("main: Current time %ld\n", res.tv_usec);
        // printf("main: Current time %ld\n", cur->tv_usec);

        printf("\nElapsed time in microseconds: %ld\n", ((res.tv_sec - cur->tv_sec)*1000000L + res.tv_usec) - cur->tv_usec); 

        shm_unlink(name);

    }


    return 0;
}