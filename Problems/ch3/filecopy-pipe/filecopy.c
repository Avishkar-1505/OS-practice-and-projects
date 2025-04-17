#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>



#define BUFFSIZE 1024
#define PERMS 0666
#define READ_END 0
#define WRITE_END 1

void execChild(int fdPipe[], char *dest){
    close(fdPipe[WRITE_END]);

    int fdDest = creat(dest, PERMS);

    if(fdDest == -1){
        printf("Failed to create destination file\n");
        printf("Error Number % d\n", errno);
        perror("Program");
        exit(1);
    }

    char buff[BUFFSIZE];
    int n;

    while((n = read(fdPipe[READ_END], buff, BUFFSIZE)) > 0){
        if(write(fdDest, buff, n) != n){
            printf("Error Writing In File\n");
            exit(1);
        }
    }

    close(fdDest);

    printf("Copied successfully\n");


}

int main(int argc, char **argv){

    if(argc != 3){
        fprintf(stderr, "Invalid number of arguments\n");
        return 1;
    }

    char *source = argv[1];
    char *dest = argv[2];

    printf("Source file dir: %s\n", source);

    printf("Destination file dir: %s\n", dest);

    const char* const sem_name = "pipe_sem";

    int fdPipe[2];

    if(pipe(fdPipe) == -1){
        fprintf(stderr, "Send Pipe Failed\n");
        return 1;
    }


    int pid = fork();

    if(pid < 0){
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if(pid==0){
        execChild(fdPipe, dest);
    }
    else{

        int fdSource = open(source, O_RDONLY);

        if(fdSource == -1){
            printf("Failed to open source file\n");
            printf("Error Number % d\n", errno);
            perror("Program");
            exit(1);
        }

        close(fdPipe[READ_END]);
        int n;
        char buff[BUFFSIZE];

        while((n = read(fdSource, buff, BUFFSIZE)) > 0){
            if (write(fdPipe[WRITE_END], buff, n) != n){
                printf("Error Writing In Pipe\n");
                break;
            }
        }

        close(fdSource);
        close(fdPipe[WRITE_END]);

        wait(NULL);
    }


    return 0;
    
}
