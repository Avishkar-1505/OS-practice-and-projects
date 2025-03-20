#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MIN_PID 300
#define MAX_PID 5000

char *map;

typedef struct stack {
    int *avail;
    int size;
} stack;

stack st;

int allocate_map() {
    free(map);
    map = (char *)malloc(sizeof(char) * (MAX_PID - MIN_PID + 2));
    
    if(map==NULL){
        return -1;
    }
    
    int i;
    for(i=0;i<(MAX_PID - MIN_PID + 1);i++){
        map[i] = '0';
    }
    
    map[i] = '\0';
    
    st.avail = (int *)malloc(sizeof(int) * (MAX_PID - MIN_PID + 1));

    if(st.avail == NULL){
        return -1;
    }

    st.size = (MAX_PID - MIN_PID + 1);

    for(i=0;i<(MAX_PID - MIN_PID + 1);i++){
        st.avail[i] = MIN_PID + i;
        printf("%d ", st.avail[i]);
    }
    printf(" \n");
    
    return 1;
}

int allocate_pid(){

    if(st.size==0){
        return -1;
    }

    int avail_pid = st.avail[st.size - 1];
    st.size--;
    st.avail = realloc(st.avail, st.size * (sizeof(int)));


    map[avail_pid - MIN_PID] = '1';
    
    return avail_pid;
}

void release_pid(int pid){
    if(map[pid - MIN_PID] == '0'){
        return;
    }

    map[pid - MIN_PID] = '0';
    st.size++;
    st.avail = realloc(st.avail, st.size * sizeof(int));
    st.avail[st.size - 1] = pid;

}


int main() {
    if(allocate_map()==-1){
        fprintf(stderr, "Failed to allocate map\n");
        free(map);
        free(st.avail);
        return 1;
    }

    int pids[10];
    
    for(int i=0;i<10;i++){
        pids[i] = allocate_pid();
        if(pids[i] == -1){
            printf("Failed to allocate pid\n");
            break;
        }
        printf("pid: %d ", pids[i]);
    }

    printf(" \n");

    release_pid(pids[0]);
    release_pid(pids[1]);

    pids[0] = allocate_pid();
    printf("pid: %d\n", pids[0]);


    
    
    free(map);
    free(st.avail);
    return 0;
}