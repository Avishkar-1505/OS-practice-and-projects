#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <fcntl.h>

#define MAX_LEN 10000

int parseArgv(char *arg){
    

    if(arg[0] == '-'){
        return -1;
    }

    int i = 0;
    int res = 0;

    while(arg[i] != '\0'){
        

        if(arg[i]=='0' && res==0){
            i++;
            continue;
        }

        if(arg[i] >='0' && arg[i] <='9'){
            res *= 10;
            res += arg[i] - '0';
            i++;
        }
        else{
            break;
        }
        
    }

    return res;
}

int main(int argc, char **argv){
    if(argc != 2){
        fprintf(stderr, "Invalid Number of Arguments\n");
        return 1;
    }

    const char *name = "SEQ";

    int fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    if(fd == -1){
        fprintf(stderr, "Creating Shared MEmory Failed\n");
        return 1;
    }


    if(ftruncate(fd, sizeof(int) * MAX_LEN) == -1){
        fprintf(stderr, "Failed to truncate shared memory\n");
        return 1;
    }

    int *ptr = (int *)mmap(NULL, sizeof(int) * MAX_LEN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if(ptr == MAP_FAILED){
        fprintf(stderr, "Mapping to shared memory failed\n");
        return 1;
    }


    pid_t pid = fork();

    if(pid < 0){
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if(pid == 0){

        int arg = parseArgv(argv[1]);

        if(arg <= 0){
            fprintf(stderr, "Invalid Argument\n");
            return 1;
        }

        int i = 0;

        while(i<MAX_LEN && arg != 1){
            ptr[i] = arg;
            if((arg&1) == 1){
                arg = arg * 3 + 1;
            }
            else{
                arg /= 2;
            }
            i++;
        }

        ptr[i] = 1;

    }
    else{
        wait(NULL);

        int i = 0;

        while(i<MAX_LEN && ptr[i]!=1){
            printf("%d, ", ptr[i]);
            i++;
        }

        printf("%d\n", ptr[i]);
        
        shm_unlink(name);
    }

    return 0;
}
