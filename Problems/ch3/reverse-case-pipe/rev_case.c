#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <semaphore.h>
#include <unistd.h>


#define BUFFER_SIZE 1000
#define READ_END 0
#define WRITE_END 1

extern int errno;



char* getString(){
    char *str = NULL, ch;
    int i = 0, j = 1;

    str = (char *)malloc(sizeof(char));
    while((ch = getc(stdin)) != '\n'){

        str = (char *)realloc(str, j * sizeof(char));
        
        str[i] = ch;
        i++;
        j++;
    }

    str[i] = '\0';
    return str;

}

void execChild(int sendPipe[], int recvPipe[]){

    close(sendPipe[WRITE_END]);
    close(recvPipe[READ_END]);

    char *message = NULL;
    message = (char *)malloc(sizeof(char));
    int i=0, j=1;

    while(1){
        char ch[1];
        int r = read(sendPipe[READ_END], ch, sizeof(char));

        if(r == -1){
            fprintf(stderr, "Read Failed in Child\n");
            exit(1);
        }

        if(r==0){
            break;
        }

        message = (char *)realloc(message, j * sizeof(char));
        message[i] = ch[0];
        i++;
        j++;

        
        if(ch[0]=='\0'){
            break;
        }

    }
    

    printf("%s\n", message);
    i = 0;
    while(message[i] != '\0'){
        if('a' <= message[i] && message[i] <= 'z'){
            message[i] -= 32; 
        }
        else if('A' <= message[i] && message[i] <= 'Z'){
            message[i] += 32;
        }

        i++;
    }

    printf("writing child %s\n", message);

    write(recvPipe[WRITE_END], message, strlen(message) + 1);

    free(message);
    
}

int main(){

    int sendPipe[2];
    int recvPipe[2];
    pid_t pid;

    const char* const sem_name = "pipe_sem";

    if(pipe(sendPipe) == -1){
        fprintf(stderr, "Send Pipe Failed\n");
        return 1;
    }

    if(pipe(recvPipe) == -1){
        fprintf(stderr, "Receive Pipe Failed\n");
        return 1;
    }

    int sem1un = sem_unlink(sem_name);
    printf("sem1un: %d\n", sem1un);
 

    sem_t *sem1 = sem_open(sem_name, O_CREAT|O_EXCL, 0644, 0);

    if(sem1 == SEM_FAILED){
        fprintf(stderr, "Semaphore failed %d\n", errno);
        if(errno == EACCES){
            printf("EACCES\n");
        }
        else if(errno == EEXIST){
            printf("EEXIST\n");
        }
        else if(errno == EINTR){
            printf("EINTR\n");
        }
        else if(errno == EINVAL){
            printf("EINVAL\n");
        }
        else if(errno == EMFILE){
            printf("EMFILE\n");
        }
        else if(errno == ENAMETOOLONG){
            printf("ENAMETOOLONG\n");
        }
        else if(errno == ENFILE){
            printf("ENFILE\n");
        }
        else if(errno == ENOENT){
            printf("ENOENT\n");
        }
        else if(errno == ENOSPC){
            printf("ENOSPC\n");
        }
        else if(errno == ENOSYS){
            printf("ENOSYS\n");
        }

        sem_unlink(sem_name);
        
        return 1;
    }


    pid = fork();


    if(pid < 0){
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if(pid == 0){
        //Child process
        sem_wait(sem1);
        printf("In Child\n");
        execChild(sendPipe, recvPipe);
        sem_post(sem1);
    }
    else{
        // Parent Process
        printf("In Parent\n");
        close(sendPipe[READ_END]);
        close(recvPipe[WRITE_END]);

        printf("Enter a message to reverse it's case: ");
        char *message = getString();
        char *recvMessage = (char *)malloc(strlen(message) + 1);
        


        // message = getString();
        printf("Writing to send pipe %s\n", message);
        write(sendPipe[WRITE_END], message, strlen(message)  + 1);

        sem_post(sem1);

        wait(NULL);

        read(recvPipe[READ_END], recvMessage, strlen(message) + 1);
        printf("Received: %s\n", recvMessage);

    }

    sem_close(sem1);
    sem_unlink(sem_name);

    return 0;
    

}
