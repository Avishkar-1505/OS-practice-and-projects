# Chapter 3 Programming Problems

1. **Creating Zombie:**

    C program that forks
    a child process that ultimately becomes a zombie process. This zombie
    process must remain in the system for at least 10 seconds.

2. **Timing Commands (Use of IPC)**

    Write a C program called time.c that determines the amount of time
    necessary to run a command from the command line. This program will
    be run as "./time command" and will report the amount of elapsed
    time to run the specified command.

    **ver1** Using shared memory region

    **ver2** Using Pipe

    **Example Output:**

    ```
    ./time ls
    time.c
    time

    Elapsed time: 0.25422
    ```

3. **Simulating Operating System’s pid manager**

    Use the following constants to identify the range of possible pid
    values:

    ```
    #define MIN PID 300
    #define MAX PID 5000
    ``` 
    You may use any data structure of your choice to represent the availability of process identifiers. One strategy is to adopt what Linux has done and use a bitmap in which a value of 0 at position i indicates that
    a process id of value i is available and a value of 1 indicates that the process id is currently in use.

    Implement the following API for obtaining and releasing a pid:
    - int allocate map(void) —> Creates and initializes a data structure for representing pids; returns −1 if unsuccessful, 1 if successful
    - int allocate pid(void) —> Allocates and returns a pid; returns
    −1 if unable to allocate a pid (all pids are in use)
    - void release pid(int pid) —> Releases a pid
    
