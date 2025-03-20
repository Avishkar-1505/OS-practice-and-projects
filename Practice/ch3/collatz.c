#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

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


    pid_t pid = fork();

    if(pid < 0){
        fprintf(stderr, "Fork Failed\n");
        return -1;
    }
    else if(pid == 0){
        int arg = parseArgv(argv[1]);

        if(arg <= 0){
            fprintf(stderr, "Invalid Argument\n");
            return 1;
        }

        while(arg != 1){
            printf("%d ", arg);
            if((arg&1) == 1){
                arg = arg * 3 + 1;
            }
            else{
                arg /= 2;
            }
        }

        printf("1\n");

    }
    else{
        wait(NULL);
    }

    return 0;
    
}