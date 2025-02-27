#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <unistd.h>
#define PERMS 0666 
#define BUFFSIZE 1024

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


int main(){
    
    char *source = NULL;
    char *dest = NULL;

    printf("Enter Source file (Relative or Absolute directory):");

    source = getString();


    if(source==NULL){
        printf("Failed to take input\n");
        exit(1);
    }


    printf("Source file dir: %s\n", source);

    printf("Enter Destination file (Relative or Absolute directory):");

    dest = getString();


    if(dest==NULL){
        printf("Failed to take input\n");
        exit(1);
    }

    printf("Destination file dir: %s\n", dest);

    int fdSource, fdDest;
    fdSource = open(source, O_RDONLY);

    if(fdSource == -1){
        printf("Failed to open source file\n");
        printf("Error Number % d\n", errno);
        perror("Program");
        exit(2);
    }
    
    fdDest = creat(dest, PERMS);

    if(fdDest == -1){
        printf("Failed to create destination file\n");
        printf("Error Number % d\n", errno);
        perror("Program");
    }

    char buf[BUFFSIZE];
    int n;

    while((n = read(fdSource, buf, 1024)) > 0){
        if (write(fdDest, buf, n) != n){
            printf("Error Writing\n");
            break;
        }
    
    }

    close(fdSource);
    close(fdDest);

    printf("Copied successfully\n");

    return 0;

}
