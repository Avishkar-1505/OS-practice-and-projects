#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define READ_END 0
#define WRITE_END 1


void execChild(int fd[], int argc, char **argv){

    close(fd[READ_END]);

    const char *childProcess = argv[1];

    struct timeval cur;
    gettimeofday(&cur, NULL);

    if(write(fd[WRITE_END], &cur, sizeof(struct timeval)) < 0){
        fprintf(stderr, "Write Failed\n");
        exit(1);
    }

    // printf("Write\n");

    close(fd[WRITE_END]);
    
    if(argc > 2){
        // int i = 1;
        
        if(execvp(childProcess, argv+1) < 0){
            fprintf(stderr, "EXEC Failed\n");
            exit(1);
        }
    }
    else{

        if(execvp(childProcess, NULL) < 0){
            fprintf(stderr, "EXEC Failed\n");
            exit(1);
        }

    }

}

int main(int argc, char *argv[]){

    if(argc < 2){
        fprintf(stderr, "Invalid number of args\n");
        return 1;
    }

    int fd[2];
    pid_t pid;

    if(pipe(fd) == -1){
        fprintf(stderr, "Pipe Failed\n");
        return 1;
    }

    pid = fork();

    if(pid < 0){
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if(pid==0){
        execChild(fd, argc, argv);
    }
    else{
        wait(NULL);
        close(fd[WRITE_END]);

        struct timeval cur;

        if(read(fd[READ_END], &cur, sizeof(struct timeval)) < 0){
            fprintf(stderr, "Read failed\n");
            return 1;
        }


        struct timeval end;
        gettimeofday(&end, NULL);

        printf("\nElapsed Time in microseconds %ld \n", end.tv_usec - cur.tv_usec);

        close(fd[READ_END]);


    }



    return 0;
}
